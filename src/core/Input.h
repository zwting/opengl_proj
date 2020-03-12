//
// Created by zwt on 2020/3/11.
//

#ifndef CMAKE_LEARN_SRC_CORE_INPUT_H_
#define CMAKE_LEARN_SRC_CORE_INPUT_H_

#include <design/Singleton.h>
#include "App.h"
#include <constant/KeyCode.h>
#include <map>

class Input: public Singleton<Input>{
    SINGLETON(Input)
 private:
  std::map<KeyCode, bool> key_status_;
 public:
  /**
   * 指定按键是否按下
   * @param key
   * @return
   */
  bool GetKey(KeyCode key);

  /**
   * 如果在这一帧按下指定按键，返回ture，否则返回false
   * @param key
   * @return ture or false
   */
  bool GetKeyDown(KeyCode key);

  /**
   * 在这一帧，指定按键是否松开
   * @param key
   * @return
   */
  bool GetKeyUp(KeyCode key);
};

#endif //CMAKE_LEARN_SRC_CORE_INPUT_H_
