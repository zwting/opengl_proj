//
// Created by zuowe on 2021/8/17.
//

#include "SceneWindow.h"
void SceneWindow::OnWindowGUI(float dt)
{
	ImGui::BeginChild("GameRender");
	ImVec2 wsize = ImGui::GetWindowSize();
	ImGui::Image((ImTextureID)mTextureColor, wsize, ImVec2(0, 1), ImVec2(1, 0));
	ImGui::EndChild();
}
SceneWindow::SceneWindow()
	:BaseWindow(static_cast<std::string&&>("GameWindow"),600,600,0,ImVec2(0, 0))
{
	mFollowParentSize = false;
}
