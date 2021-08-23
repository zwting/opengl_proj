//
// Created by zuowe on 2021/8/17.
//

#ifndef FANCY_ENGINE_SRC_EVENT_EVENTMGR_H_
#define FANCY_ENGINE_SRC_EVENT_EVENTMGR_H_

#include "design/Singleton.h"
#include <map>
#include <vector>
#include <constant/CommonDefine.h>

class EventMgr: public Singleton<EventMgr>
{
	SINGLETON(EventMgr)
 private:
	std::map<EEventType, std::vector<EventHandler>> mEventHandlerMap;

 public:
	void RegisterEvent(EEventType event_type, EventHandler event_handler)
	{
		auto event_list = mEventHandlerMap[event_type];
		auto find_ret = std::find(event_list.begin(), event_list.end(), event_handler);
		if(find_ret != event_list.end())
		{
			return;
		}
		event_list.emplace_back(event_handler);
	}

	void UnRegisterEvent(EEventType event_type, EventHandler event_handler)
	{
		auto event_list = mEventHandlerMap[event_type];
		auto find_ret = std::find(event_list.begin(), event_list.end(), event_handler);
		if(find_ret == event_list.end())
		{
			return;
		}
		event_list.erase(std::remove(event_list.begin(), event_list.end(), event_handler), event_list.end());
	}

};

#endif //FANCY_ENGINE_SRC_EVENT_EVENTMGR_H_
