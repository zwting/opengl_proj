//
// Created by zuowe on 2021/8/16.
//

#ifndef FANCY_ENGINE_SRC_GUI_WINDOWMGR_H_
#define FANCY_ENGINE_SRC_GUI_WINDOWMGR_H_
#include <vector>
#include <design/Singleton.h>
#include "BaseWindow.h"

class WindowMgr : public Singleton<WindowMgr>
{
 private:
	SINGLETON(WindowMgr)
	std::vector<BaseWindow*> mWindowList;

 public:
	void RegisterWindow(BaseWindow* window)
	{
		const auto findRet = std::find(mWindowList.begin(), mWindowList.end(), window);
		if(findRet != mWindowList.end())
		{
			return;
		}
		mWindowList.emplace_back(window);
	}

	void UnRegisterWindow(BaseWindow* window)
	{
		const auto findRet = std::find(mWindowList.begin(), mWindowList.end(), window);
		if(findRet == mWindowList.end())
		{
			return;
		}
		mWindowList.erase(findRet);
	}

	void Update(float dt)
	{
		for(auto it : mWindowList)
		{
			if(!it->IsVisible())
				continue;
			it->OnGUI(dt);
		}
	}
};

#endif //FANCY_ENGINE_SRC_GUI_WINDOWMGR_H_
