//
// Created by zwt on 2020/3/10.
//

#include <cstdio>
#include <glad/glad.h>
#include <utils/Debug.h>
#include <gui/WindowMgr.h>
#include <gui/MainWindow.h>
#include "App.h"

#include "Camera.h"
#include "Shader.h"
#include "Model.h"
#include "PrimitiveModel.h"
#include "Time.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"


Shader* g_shader = nullptr;
Model* g_model = nullptr;
Transform* g_node = nullptr;
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
	return mWidth;
}

int App::GetHeight() const
{
	return mHeight;
}

int App::GetFPS() const
{
	return mFps;
}

const char* App::GetTitle() const
{
	return mTitle;
}

GLFWwindow* App::window()
{
	return mWindow;
}

void App::ImGUIBackendInit(GLFWwindow* window, const char* glsl_version)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigWindowsMoveFromTitleBarOnly = true;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = true;
	//io.ConfigViewportsNoTaskBarIcon = true;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Read 'docs/FONTS.md' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != NULL);


}

bool App::Init(const char* title, int width, int height)
{
	mTitle = title;
	mWidth = width;
	mHeight = height;

	SetupCallbacks();

	if (!glfwInit())
	{
		return false;
	}

	// Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
	// GL ES 2.0 + GLSL 100
	const char* glsl_version = "#version 100";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
	// GL 3.2 + GLSL 150
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
	// const char* glsl_version = "#version 130";
	const char* glsl_version = "#version 330";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	mWindow = glfwCreateWindow(mWidth, mHeight, mTitle, nullptr, nullptr);

	if (!mWindow)
	{
		fprintf(stderr, "Unable to create GLFW window\n");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(mWindow);
	glfwSwapInterval(1); // Enable vsync

	int gladInitRes = gladLoadGL();
	if (!gladInitRes)
	{
		fprintf(stderr, "Unable to initialize glad\n");
		glfwDestroyWindow(mWindow);
		glfwTerminate();
		return false;
	}

	InitFBO();
	ImGUIBackendInit(mWindow, glsl_version);
	InitWindows();

	Time::instance()->Init();
	InitLogicTmp();
	mIsInitFinished = true;

	return true;
}

void App::ErrorCallback(int error, const char* description)
{
	//TODO: 错误记录到日志
	fprintf(stderr, "GLFW error %d: %s\n", error, description);
}

void App::SetupCallbacks()
{
	//设置错误回调方法
	glfwSetErrorCallback(ErrorCallback);
}

void App::Run()
{
	ImGuiIO& io = ImGui::GetIO();

	while (!glfwWindowShouldClose(mWindow))
	{
		glfwPollEvents();

		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
		Clear();

		int display_w, display_h;
		glfwGetFramebufferSize(mWindow, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);

		Time::instance()->Update();
		const double dt = Time::instance()->GetDeltaTime();

		Update(dt);
		Render(dt);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		Clear();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		RenderGUI(dt);
		WindowMgr::instance()->Update(dt);

		// Rendering
		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}


		glfwSwapBuffers(mWindow);
	}

	glfwDestroyWindow(mWindow);
	glfwTerminate();
}


void App::Update(const double dt)
{
}

void App::RenderGUI(const double dt)
{
	static bool show_demo_window = true;
	ImGui::ShowDemoWindow(&show_demo_window);
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
	const float aspect = static_cast<float>(mWidth) / static_cast<float>(mHeight);
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
	return mIsInitFinished;
}
void App::InitFBO()
{
	glGenFramebuffers(1, &mFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

	glGenTextures(1, &mTextureColorBuffer);
	glBindTexture(GL_TEXTURE_2D, mTextureColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTextureColorBuffer, 0);

	glGenRenderbuffers(1, &mRBO);
	glBindRenderbuffer(GL_RENDERBUFFER, mRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mWidth, mHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRBO);
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		Debug::instance()->Error("Create FrameBuffer Failed!!");
		return;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void App::Clear()
{
	const glm::vec4 clear_color(0.1f, 0.1f, 0.1f, 1.0);
	glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
		clear_color.w);
	int clearFlag = GL_COLOR_BUFFER_BIT;
	if (glIsEnabled(GL_DEPTH_TEST)) clearFlag |= GL_DEPTH_BUFFER_BIT;
	if (glIsEnabled(GL_STENCIL_TEST)) clearFlag |= GL_STENCIL_BUFFER_BIT;
	glClear(GL_COLOR_BUFFER_BIT);
}
void App::InitWindows()
{
	WindowMgr::instance()->RegisterWindow(new MainWindow(mWidth, mHeight));
	mSceneWindow = new SceneWindow();
	mSceneWindow->SetTextureColor(mTextureColorBuffer);
	WindowMgr::instance()->RegisterWindow(mSceneWindow);
}
