//
// Created by zuowe on 2021/8/14.
//

#ifndef FANCY_ENGINE_BASEWINDOW_H
#define FANCY_ENGINE_BASEWINDOW_H

#include <string>
#include "imgui.h"

class BaseWindow
{
 protected:
	int mWidth;
	int mHeight;
	std::string mTitle;
	int mWindowFlags;
	bool mIsVisible;
	bool mFollowParentSize;
	int mImGuiCond;
	ImVec2 mPos;

 public:
	void AddWindowFlags(int flags){ mWindowFlags |= flags;}
	void SetWindowFlags(int flags) {mWindowFlags = flags;}
	void RemoveWindowFlags(int flags){ mWindowFlags &= ~flags; }
	int GetWindowFlags() const {return mWindowFlags;}

	std::string GetTitle() const {return mTitle;}
	void SetTitle(std::string && title){mTitle = std::move(title);}

	bool IsVisible()const{return mIsVisible;}
	void SetVisible(bool isVisible) {mIsVisible = isVisible;}

	void SetPos(float x, float y) {mPos.x = x ; mPos.y = y;}
	const ImVec2& GetPos()const{return mPos;}

	void SetFollowParentSize(bool isFollow) {mFollowParentSize = isFollow;}

 public:
	virtual void OnGUI(float dt);
	BaseWindow(std::string&& title, int width, int height, int flags, ImVec2&& pos=ImVec2(-1, -1));

 protected:
	virtual void OnWindowGUI(float dt) = 0;

};

#endif //FANCY_ENGINE_BASEWINDOW_H
