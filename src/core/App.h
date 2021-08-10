//
// Created by zwt on 2020/3/10.
//

#ifndef CMAKE_LEARN_APP_H
#define CMAKE_LEARN_APP_H

#include <glfw/glfw3.h>
#include <design/Singleton.h>
#include "Input.h"
#include <iostream>

class App : public Singleton<App> {
 private:
  GLFWwindow *window_;
  int width_;
  int height_;
  int fps_;
  const char *title_;
  int init_complete_;
 private:
  //=================回调方法==================
  /**
   * 错误回调
   * @param error
   * @param description
   */
  static void error_callback(int error, const char *description);

 private:
  //=====================内部回调方法======================
  /**
   * 初始化各种回调方法
   */
  void setup_callbacks();
 private:
  //======================构造方法=========================
  SINGLETON(App)
 public:
  //=====================getter setter=====================
  GLFWwindow *window();
  int width() const;
  int height() const;
  int fps() const;
  const char *title() const;
  int init_complete() const;

 public:
  //======================对外接口======================
  bool Init(const char *title, int width, int height);
  void Run();
 protected:
  //=======================内部方法=======================
  void Update(const double dt);
  void Render(const double dt);
};

//创建单例
//SINGLETON(App)
#endif //CMAKE_LEARN_APP_H
