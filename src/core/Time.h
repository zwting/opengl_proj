//
// Created by zwt on 2020/3/11.
//

#ifndef CMAKE_LEARN_SRC_CORE_TIME_H_
#define CMAKE_LEARN_SRC_CORE_TIME_H_

#include <design/Singleton.h>
#include <glfw/glfw3.h>

class Time : public Singleton<Time>
{
    SINGLETON_CTR(Time)
private:
    double _time_elapsed;
    double _delta_time;

    Time() : _time_elapsed(0)
    {
    }

public:
    void Init()
    {
        _time_elapsed = glfwGetTime();
    }

    void Update()
    {
        const double cur_time = GetTime();
        _delta_time = cur_time - _time_elapsed;
        _time_elapsed = cur_time;
    }

    inline double GetTime() const { return glfwGetTime(); }
    inline double GetDeltaTime() const { return _delta_time; }
};

typedef Singleton<Time> TimeInstance;

#endif //CMAKE_LEARN_SRC_CORE_TIME_H_
