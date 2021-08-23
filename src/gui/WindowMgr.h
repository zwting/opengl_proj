//
// Created by zuowe on 2021/8/16.
//

#ifndef FANCY_ENGINE_SRC_GUI_WINDOWMGR_H_
#define FANCY_ENGINE_SRC_GUI_WINDOWMGR_H_
#include <map>
#include <design/Singleton.h>
#include <constant/CommonDefine.h>
#include "BaseWindow.h"

class WindowMgr : public Singleton<WindowMgr>
{
 private:
	SINGLETON(WindowMgr)
	std::map<EWindowType, BaseWindow*> mWindowMap;

 public:
	void RegisterWindow(BaseWindow* window)
	{
		const auto win_type = window->GetWindowType();
		if(mWindowMap.find(win_type) != mWindowMap.end())
			return;
		mWindowMap[win_type] = window;
	}

	void UnRegisterWindow(BaseWindow* window)
	{
		const auto win_type = window->GetWindowType();
		const auto find_ret = mWindowMap.find(win_type);
		if( find_ret == mWindowMap.end())
			return;
		mWindowMap.erase(find_ret);
	}

	BaseWindow* GetWindowByType(EWindowType type)
	{
		const auto find_ret = mWindowMap.find(type);
		if(find_ret != mWindowMap.end())
			return find_ret->second;

		return nullptr;
	}

	void Update(float dt)
	{
		for(auto it : mWindowMap)
		{
			if(!it.second->IsVisible())
				continue;
			it.second->OnGUI(dt);
		}
	}
};

#endif //FANCY_ENGINE_SRC_GUI_WINDOWMGR_H_
