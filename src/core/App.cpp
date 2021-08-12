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

void App::Render(const double dt)
{
	g_shader->Use();
	g_shader->SetFloat("roughness", 0.2f);
	g_shader->SetFloat("metallic", 0.4f);
	g_shader->SetVec3("albedo", glm::vec3(0.0f, 0.0f, 0.8f));
	g_shader->SetFloat("ao", 1.0f);
	for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
	{
		glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
		newPos = lightPositions[i];
		std::string lightStr = "lightPositions[" + std::to_string(i) + "]";
		g_shader->SetVec3(lightStr.c_str(), newPos);
		lightStr = "lightColors[" + std::to_string(i) + "]";
		g_shader->SetVec3(lightStr.c_str(), lightColors[i]);
	}

	g_node->Render(g_shader);
}

void App::InitLogicTmp()
{
	g_shader = new Shader("res/shader/pbr.vert", "res/shader/pbr.frag");
	g_shader->Use();
	const float aspect = static_cast<float>(width_) / static_cast<float>(height_);
	g_camera = new Camera(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), 45.0f, aspect, 0.1f, 100);
	g_camera->Active();
	g_camera->LookAt(glm::vec3(0, 0, 0));
	g_node = PrimitiveModel::CreatePrimitive(PrimitiveModel::PrimitiveType::Sphere);
	g_node->SetScale(0.5f);
	g_node->SetPosition(glm::zero<vec3>());
	// g_shader->SetMat4vf("view", glm::value_ptr(g_camera->GetViewMatrix()));
	// g_shader->SetMat4vf("proj", glm::value_ptr(g_camera->GetProjMatrix()));

	glEnable(GL_CULL_FACE);
}

int App::InitComplete() const
{
	return init_complete_;
}
