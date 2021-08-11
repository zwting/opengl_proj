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
    glm::vec3(-10.0f,  10.0f, 10.0f),
    glm::vec3(10.0f,  10.0f, 10.0f),
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


int App::GetWidth() const {
    return width_;
}
int App::GetHeight() const {
    return height_;
}
int App::GetFPS() const {
    return fps_;
}
const char *App::GetTitle() const {
    return title_;
}
GLFWwindow *App::window() {
    return window_;
}
bool App::Init(const char *title, int width, int height) {
    title_ = title;
    width_ = width;
    height_ = height;

    setup_callbacks();

    if(!glfwInit()){
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window_ = glfwCreateWindow(width_, height_, title_, nullptr, nullptr);

    if (!window_) {
        fprintf(stderr, "Unable to create GLFW window\n");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window_);

    int gladInitRes = gladLoadGL();
    if (!gladInitRes) {
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
void App::error_callback(int error, const char *description) {
    //TODO: 错误记录到日志
    fprintf(stderr, "GLFW error %d: %s\n", error, description);
}
void App::setup_callbacks() {
    //设置错误回调方法
    glfwSetErrorCallback(error_callback);
}

void App::Run() {
    glClearColor(0.15f, 0.6f, 0.4f, 1.0f);

    while (!glfwWindowShouldClose(window_)) {
        glClear(GL_COLOR_BUFFER_BIT);

        Time::instance()->Update();
        const double dt = Time::instance()->GetDeltaTime();
        Update(dt);
        Render(dt);

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
	
}

void App::InitLogicTmp()
{
    g_shader = new Shader("res/shader/pbr.vert", "res/shader/pbr.frag");
    g_shader->Use();
    g_camera = new Camera(glm::vec3(0, 0, -10), glm::vec3(0, 0, 0), 45, width_ / (float)height_, 0, 100);
    g_node = PrimitiveModel::CreatePrimitive(PrimitiveModel::PrimitiveType::Sphere);
}

int App::InitComplete() const {
    return init_complete_;
}
