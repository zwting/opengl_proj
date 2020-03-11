//
// Created by zwt on 2020/3/11.
//

#include <constant/KeyCode.h>
#include "Input.h"
#include <glfw/glfw3.h>

bool Input::GetKey(KeyCode key) {
    assert(App::instance()->init_complete());
    return glfwGetKey(App::instance()->window(), static_cast<int>(key)) == GLFW_PRESS;
}
bool Input::GetKeyDown(KeyCode key) {
    auto is_press = key_status_[key];
    if(is_press){
        return false;
        key_status_[key] = glfwGetKey(App::instance()->window(), static_cast<int>(key)) == GLFW_PRESS;
    }
    return false;
}
bool Input::GetKeyUp(KeyCode key) {
    return false;
}
