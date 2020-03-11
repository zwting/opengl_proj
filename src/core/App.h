//
// Created by zwt on 2020/3/10.
//

#ifndef CMAKE_LEARN_APP_H
#define CMAKE_LEARN_APP_H

#include <glfw/glfw3.h>
#include <design/Singleton.h>

class App{
 private:
  GLFWwindow *window_;
  int width_;
  int height_;
  int fps_;
  const char *title_;
 private:
  //---------------回调方法-----------------
  /**
   * 错误回调
   * @param error
   * @param description
   */
  static void error_callback(int error, const char* description);

 private:
  //---------------内部方法-----------------
  /**
   * 初始化各种回调方法
   */
  void setup_callbacks();
 public:
  //---------------getter setter------------------
  GLFWwindow *window();
  int width() const;
  int height() const;
  int fps() const;
  const char *title() const;

 public:
    bool Init(const char* title, int width, int height);
    void Run();
    void Update();
};

//创建单例
SINGLETON(App)
#endif //CMAKE_LEARN_APP_H
