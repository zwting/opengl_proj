#include "Shader.h"
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Camera.h"
#include "utils/Debug.h"

const Shader* Shader::CurShader = nullptr;

Shader::Shader(const char* vertexPath, const char* fragPath)
{
	assert(vertexPath && fragPath);

	try
	{
		std::fstream vertexStream(vertexPath, std::ios_base::in);
		std::fstream fragStream(fragPath, std::ios_base::in);
		std::stringstream vertexBuffer;
		std::stringstream fragBuffer;

		vertexBuffer << vertexStream.rdbuf();
		mVertexSrc = vertexBuffer.str();
		vertexStream.close();

		fragBuffer << fragStream.rdbuf();
		mFragSrc = fragBuffer.str();
		fragStream.close();
	}
	catch (std::ifstream::failure e)
	{
		Debug::instance()->Log("Error: shader file not successfuly read");
	}

	mVertexID = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertexCSrc = mVertexSrc.c_str();
	if (!Compile(mVertexID, vertexCSrc))
		return;

	mFragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragmentSrc = mFragSrc.c_str();
	if (!Compile(mFragmentID, fragmentSrc))
		return;

	mProgram = glCreateProgram();

	glAttachShader(mProgram, mVertexID);
	glAttachShader(mProgram, mFragmentID);
	glLinkProgram(mProgram);

	int success;
	glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		memset(mLogBuffer, 0, sizeof(mLogBuffer));
		glGetProgramInfoLog(mProgram, sizeof(mLogBuffer) / sizeof(char), nullptr, mLogBuffer);
		Debug::instance()->Log("Error: Shader program linking failed:\n {0}", mLogBuffer);
		return;
	}

	glDeleteShader(mVertexID);
	glDeleteShader(mFragmentID);
}

void Shader::SetVec4(const char* variable, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const
{
	const GLint location = glGetUniformLocation(this->mProgram, variable);
	glUniform4f(location, x, y, z, w);
}

void Shader::SetVec3(const char* variable, const vec3& val) const
{
	const GLint location = glGetUniformLocation(this->mProgram, variable);
	glUniform3f(location, val.x, val.y, val.z);
}


void Shader::SetFloat(const char* variable, float val) const

{
	const GLint location = glGetUniformLocation(this->mProgram, variable);
	glUniform1f(location, val);
}

void Shader::SetInt(const char* variable, int val) const
{
	const GLint location = glGetUniformLocation(this->mProgram, variable);
	glUniform1i(location, val);
}

void Shader::SetMat4vf(const char* variable, const GLfloat* val) const
{
	const GLint location = glGetUniformLocation(this->mProgram, variable);
	glUniformMatrix4fv(location, 1, GL_FALSE, val);
}

void Shader::Use() const
{
	glUseProgram(mProgram);
	if (Camera::GetCurrent())
	{
		SetMat4vf("proj",VALUE_PTR(Camera::GetCurrent()->GetProjMatrix()));
		SetMat4vf("view",VALUE_PTR(Camera::GetCurrent()->GetViewMatrix()));
		SetVec3("camera_pos", Camera::GetCurrent()->GetPosition());
	}
	Shader::CurShader = this;
}


bool Shader::Compile(GLuint shaderID, const char* src)
{
	glShaderSource(shaderID, 1, &src, nullptr);

	glCompileShader(shaderID);
	int success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		memset(mLogBuffer, 0, sizeof(mLogBuffer));
		glGetShaderInfoLog(shaderID, sizeof(mLogBuffer) / sizeof(char), nullptr, mLogBuffer);
		char* shaderType = shaderID == mVertexID ? "vertex" : "fragment";
		Debug::instance()->Log("Error: {0} shader compilation failed:\n {1}", shaderType, mLogBuffer);
		return false;
	}

	return true;
}
