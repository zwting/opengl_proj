//
// Created by zwt on 2020/3/11.
//

#include <constant/KeyCode.h>
#include "Input.h"
#include <glfw/glfw3.h>
#include <cassert>

bool Input::GetKey(KeyCode key) {
    assert(App::instance()->InitComplete());

    return glfwGetKey(App::instance()->window(), static_cast<int>(key)) == GLFW_PRESS;
}


bool Input::GetKeyDown(KeyCode key) {
    assert(App::instance()->InitComplete());

    auto is_press = key_status_[key];
    auto is_press_cur_frame = glfwGetKey(App::instance()->window(), static_cast<int>(key)) == GLFW_PRESS;

    if(is_press){
        return false;
    }

    if(is_press_cur_frame){
        key_status_[key] = true;
        return true;
    }
    return false;
}


bool Input::GetKeyUp(KeyCode key) {
    assert(App::instance()->InitComplete());

    auto is_press = key_status_[key];
    auto is_release_cur_frame = glfwGetKey(App::instance()->window(), static_cast<int>(key)) == GLFW_RELEASE;

    if(!is_press){
        return false;
    }
    if(is_release_cur_frame){
        key_status_[key] = false;
        return true;
    }
    return false;
}
