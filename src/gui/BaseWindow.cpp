//
// Created by zuowe on 2021/8/14.
//

#include <imgui.h>
#include "BaseWindow.h"
void BaseWindow::OnGUI(float dt)
{
	const auto viewPort = ImGui::GetWindowViewport();
	ImVec2 pos = mPos;
	if (mFollowParentSize)
	{
		mWidth = viewPort->WorkSize.x;
		mHeight = viewPort->WorkSize.y;
		pos.x = viewPort->WorkPos.x + mPos.x;
		pos.y =viewPort->WorkPos.y + mPos.y;
	}
	ImGui::SetNextWindowSize(ImVec2(mWidth, mHeight), mImGuiCond);
	ImGui::SetNextWindowPos(pos, mImGuiCond);
	if (!ImGui::Begin(mTitle.c_str(), &mIsVisible, mWindowFlags))
	{
		ImGui::End();
		return;
	}

	OnWindowGUI(dt);

	ImGui::End();
}
BaseWindow::BaseWindow(std::string&& title, int width, int height, int flags, ImVec2&& pos)
	:mPos(pos), mWidth(width), mHeight(height), mTitle(title), mWindowFlags(flags),
	mImGuiCond(ImGuiCond_FirstUseEver)
{

}
