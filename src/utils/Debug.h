//
// Created by zwt on 2020/3/12.
//

#ifndef CMAKE_LEARN_SRC_UTILS_DEBUG_H_
#define CMAKE_LEARN_SRC_UTILS_DEBUG_H_

#include <cstdio>
#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "design/Singleton.h"

#define DEFINE_LOG_FUNC(FUNC_NAME, LOGGER_METHOD_NAME) \
template <typename T>	\
void FUNC_NAME(const T& msg)	\
{	\
	_main_logger->LOGGER_METHOD_NAME(msg);	\
}                                                      \
template <typename... Args>	\
void FUNC_NAME(fmt::format_string<Args...> fmt, Args&& ...args)	\
{	\
	_main_logger->LOGGER_METHOD_NAME(fmt, args...);	\
}

class Debug : public Singleton<Debug>
{
	SINGLETON_CTR(Debug)
private:
	std::shared_ptr<spdlog::logger> _main_logger;
	Debug()
	{
		const int max_size = 1024 * 1024 * 5;
		const int max_files = 5;
		std::vector<spdlog::sink_ptr> sinks;
		sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
		sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/main-log.txt", max_size, max_files));
		_main_logger = std::make_shared<spdlog::logger>("MAIN", begin(sinks), end(sinks));
		//register it if you need to access it globally
		spdlog::register_logger(_main_logger);
	}
public:
	DEFINE_LOG_FUNC(Log, info)
	DEFINE_LOG_FUNC(Error, error)
};

#endif //CMAKE_LEARN_SRC_UTILS_DEBUG_H_
