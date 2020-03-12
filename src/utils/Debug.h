//
// Created by zwt on 2020/3/12.
//

#ifndef CMAKE_LEARN_SRC_UTILS_DEBUG_H_
#define CMAKE_LEARN_SRC_UTILS_DEBUG_H_

#include <cstdio>

class Debug {
 public:

  template <typename... Types>
  inline static void Log(const char* format, Types... args){
      fprintf(stderr, format, args...);
      fprintf(stderr, "\n");
  };

  static void LogWarning(const char *msg, ...);

  static void LogError(const char *msg, ...);

};

#endif //CMAKE_LEARN_SRC_UTILS_DEBUG_H_
