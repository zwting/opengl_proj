//
// Created by zwt on 2020/3/10.
//

#include <cstdio>
#include <glad/glad.h>
#include "App.h"

int App::width() const {
    return width_;
}
int App::height() const {
    return height_;
}
int App::fps() const {
    return fps_;
}
const char *App::title() const {
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

        Update();

        glfwSwapBuffers(window_);
        glfwPollEvents();
    }

    glfwDestroyWindow(window_);
    glfwTerminate();
}
void App::Update() {

}
int App::init_complete() const {
    return init_complete_;
}
