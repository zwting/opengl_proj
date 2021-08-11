//
// Created by zwt on 2020/3/10.
//

#include <cstdio>
#include <glad/glad.h>
#include <utils/Debug.h>
#include "App.h"

#include "Camera.h"
#include "Shader.h"
#include "Model.h"
#include "PrimitiveModel.h"
#include "Time.h"


Shader* g_shader = nullptr;
Model* g_model = nullptr;
Node* g_node = nullptr;
Camera* g_camera = nullptr;


// lights
// ------
glm::vec3 lightPositions[] = {
	glm::vec3(-10.0f, 10.0f, 10.0f),
	glm::vec3(10.0f, 10.0f, 10.0f),
	glm::vec3(-10.0f, -10.0f, 10.0f),
	glm::vec3(10.0f, -10.0f, 10.0f),
};
glm::vec3 lightColors[] = {
	glm::vec3(300.0f, 300.0f, 300.0f),
	glm::vec3(300.0f, 300.0f, 300.0f),
	glm::vec3(300.0f, 300.0f, 300.0f),
	glm::vec3(300.0f, 300.0f, 300.0f)
};
int nrRows = 7;
int nrColumns = 7;
float spacing = 2.5;


int App::GetWidth() const
{
	return width_;
}

int App::GetHeight() const
{
	return height_;
}

int App::GetFPS() const
{
	return fps_;
}

const char* App::GetTitle() const
{
	return title_;
}

GLFWwindow* App::window()
{
	return window_;
}

bool App::Init(const char* title, int width, int height)
{
	title_ = title;
	width_ = width;
	height_ = height;

	setup_callbacks();

	if (!glfwInit())
	{
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window_ = glfwCreateWindow(width_, height_, title_, nullptr, nullptr);

	if (!window_)
	{
		fprintf(stderr, "Unable to create GLFW window\n");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window_);

	int gladInitRes = gladLoadGL();
	if (!gladInitRes)
	{
		fprintf(stderr, "Unable to initialize glad\n");
		glfwDestroyWindow(window_);
		glfwTerminate();
		return false;
	}

	Time::instance()->Init();
	InitLogicTmp();
	init_complete_ = true;

	return true;
}

void App::error_callback(int error, const char* description)
{
	//TODO: 错误记录到日志
	fprintf(stderr, "GLFW error %d: %s\n", error, description);
}

void App::setup_callbacks()
{
	//设置错误回调方法
	glfwSetErrorCallback(error_callback);
}

void App::Run()
{
	while (!glfwWindowShouldClose(window_))
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1);
		int clearFlag = GL_COLOR_BUFFER_BIT;
		if (glIsEnabled(GL_DEPTH_TEST)) clearFlag |= GL_DEPTH_BUFFER_BIT;
		if (glIsEnabled(GL_STENCIL_TEST)) clearFlag |= GL_STENCIL_BUFFER_BIT;
		glClear(GL_COLOR_BUFFER_BIT);

		Time::instance()->Update();
		const double dt = Time::instance()->GetDeltaTime();
		Update(dt);
		Render(dt);
		Sleep(8);

		glfwSwapBuffers(window_);
		glfwPollEvents();
	}

	glfwDestroyWindow(window_);
	glfwTerminate();
}


void App::Update(const double dt)
{
}

unsigned int sphereVAO = 0;
unsigned int indexCount;

void renderSphere()
{
	if (sphereVAO == 0)
	{
		glGenVertexArrays(1, &sphereVAO);

		unsigned int vbo, ebo;
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		std::vector<glm::vec3> positions;
		std::vector<glm::vec2> uv;
		std::vector<glm::vec3> normals;
		std::vector<unsigned int> indices;

		const unsigned int X_SEGMENTS = 64;
		const unsigned int Y_SEGMENTS = 64;
		const float PI = 3.14159265359;
		for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
		{
			for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
			{
				float xSegment = (float)x / (float)X_SEGMENTS;
				float ySegment = (float)y / (float)Y_SEGMENTS;
				float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
				float yPos = std::cos(ySegment * PI);
				float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

				positions.push_back(glm::vec3(xPos, yPos, zPos));
				uv.push_back(glm::vec2(xSegment, ySegment));
				normals.push_back(glm::vec3(xPos, yPos, zPos));
			}
		}

		bool oddRow = false;
		for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
		{
			if (!oddRow) // even rows: y == 0, y == 2; and so on
			{
				for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
				{
					indices.push_back(y * (X_SEGMENTS + 1) + x);
					indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
				}
			}
			else
			{
				for (int x = X_SEGMENTS; x >= 0; --x)
				{
					indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
					indices.push_back(y * (X_SEGMENTS + 1) + x);
				}
			}
			oddRow = !oddRow;
		}
		indexCount = indices.size();

		std::vector<float> data;
		for (unsigned int i = 0; i < positions.size(); ++i)
		{
			data.push_back(positions[i].x);
			data.push_back(positions[i].y);
			data.push_back(positions[i].z);
			if (uv.size() > 0)
			{
				data.push_back(uv[i].x);
				data.push_back(uv[i].y);
			}
			if (normals.size() > 0)
			{
				data.push_back(normals[i].x);
				data.push_back(normals[i].y);
				data.push_back(normals[i].z);
			}
		}
		glBindVertexArray(sphereVAO);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		float stride = (3 + 2 + 3) * sizeof(float);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(5 * sizeof(float)));
	}

	glBindVertexArray(sphereVAO);
	glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
}

void App::Render(const double dt)
{
	g_shader->Use();
	g_shader->SetFloat("roughness", 0.1f);
	g_shader->SetVec3("camPos", g_camera->GetPosition());

	glm::mat4 model = glm::mat4(1.0f);
	for (int row = 0; row < nrRows; ++row)
	{
		g_shader->SetFloat("metallic", (float)row / (float)nrRows);
		for (int col = 0; col < nrColumns; ++col)
		{
			// we clamp the roughness to 0.05 - 1.0 as perfectly smooth surfaces (roughness of 0.0) tend to look a bit off
			// on direct lighting.
			g_shader->SetFloat("roughness", glm::clamp((float)col / (float)nrColumns, 0.05f, 1.0f));

			// model = glm::mat4(1.0f);
			// model = glm::translate(model, glm::vec3(
			//     (col - (nrColumns / 2)) * spacing,
			//     (row - (nrRows / 2)) * spacing,
			//     0.0f
			// ));
			// g_shader->SetMat4vf("model", value_ptr(model));
			g_node->SetPosition(glm::vec3(
				(col - (nrColumns / 2)) * spacing,
				(row - (nrRows / 2)) * spacing,
				0.0f
			));
			g_node->Render(g_shader);
			// renderSphere();
		}
	}

	for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
	{
		glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
		newPos = lightPositions[i];
		std::string lightStr = "lightPositions[" + std::to_string(i) + "]";
		g_shader->SetVec3(lightStr.c_str(), newPos);
		lightStr = "lightColors[" + std::to_string(i) + "]";
		g_shader->SetVec3(lightStr.c_str(), lightColors[i]);

		// model = glm::translate(model, newPos);
		// model = glm::scale(model, glm::vec3(0.5f));
		// g_shader->SetMat4vf("model", value_ptr(model));
		//
		g_node->SetScale(glm::vec3(0.5f));
		g_node->SetPosition(newPos);
		g_node->Render(g_shader);
		// renderSphere();
	}
}

void App::InitLogicTmp()
{
	g_shader = new Shader("res/shader/pbr.vert", "res/shader/pbr.frag");
	g_shader->Use();
	g_shader->SetVec3("albedo", glm::vec3(0.5f, 0.0f, 0.0f));
	g_shader->SetFloat("ao", 1.0f);
	const float aspect = static_cast<float>(width_) / static_cast<float>(height_);
	g_camera = new Camera(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), 45.0f, aspect, 0.1f, 100);
	g_camera->Active();
	g_camera->LookAt(glm::vec3(0, 0, 0));
	g_node = PrimitiveModel::CreatePrimitive(PrimitiveModel::PrimitiveType::Cube);
	g_node->SetPosition(glm::zero<vec3>());
	g_shader->SetMat4vf("view", glm::value_ptr(g_camera->GetViewMatrix()));
	g_shader->SetMat4vf("proj", glm::value_ptr(g_camera->GetProjMatrix()));
}

int App::InitComplete() const
{
	return init_complete_;
}
