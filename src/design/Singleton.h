//
// Created by zwt on 2020/3/11.
//

#ifndef CMAKE_LEARN_SRC_DESIGN_SINGLETON_H_
#define CMAKE_LEARN_SRC_DESIGN_SINGLETON_H_

template <class T>
class Singleton {
 private:
  static T *instance_;
 private:
  Singleton(Singleton const&);
  Singleton& operator=(Singleton const&);
 public:
  static T *Instance() {
      if(instance_ == nullptr){
          instance_ = new T();
      }
      return instance_;
  }

};
template <class T> T* Singleton<T>::instance_ = nullptr;

#define SINGLETON(T) typedef Singleton<T> T##Instance;
#endif //CMAKE_LEARN_SRC_DESIGN_SINGLETON_H_
