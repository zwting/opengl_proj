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
  bool GetKey(KeyCode key);
  bool GetKeyDown(KeyCode key);
  bool GetKeyUp(KeyCode key);
};

#endif //CMAKE_LEARN_SRC_CORE_INPUT_H_
