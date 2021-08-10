//
// Created by zwt on 2020/3/11.
//

#ifndef CMAKE_LEARN_SRC_DESIGN_SINGLETON_H_
#define CMAKE_LEARN_SRC_DESIGN_SINGLETON_H_

template <class T>
class Singleton
{
protected:
	static T* instance_;
	Singleton() = default;
	Singleton(Singleton const&) = delete;
	Singleton& operator=(Singleton const&) = delete;
public:
	static T* instance()
	{
		if (instance_ == nullptr)
		{
			instance_ = new T;
		}
		return instance_;
	}
};

template <class T>
T* Singleton<T>::instance_ = nullptr;

//#define SINGLETON(T) typedef Singleton<T> T##Instance;

//声明单例
#define SINGLETON_CTR(T)    \
 private:               \
  friend Singleton<T>;  \


//声明单例
#define SINGLETON(T)    \
 private:               \
  friend Singleton<T>;  \
  T() = default;
#endif //CMAKE_LEARN_SRC_DESIGN_SINGLETON_H_
