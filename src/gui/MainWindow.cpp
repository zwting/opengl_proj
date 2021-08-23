//
// Created by zuowe on 2021/8/16.
//

#include "MainWindow.h"
MainWindow::MainWindow(int width, int height)
	:BaseWindow("MainWindow", width, height, 0)
{
	mTitle = "Main Windows";
	mPos = {0, 0};
	mFollowParentSize = true;
	mImGuiCond = 0;
	mWindowFlags = ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoScrollbar		|
		ImGuiWindowFlags_NoMove				|
		ImGuiWindowFlags_NoResize|
		ImGuiWindowFlags_NoCollapse|
		ImGuiWindowFlags_MenuBar |
		ImGuiWindowFlags_NoBackground;
}

void MainWindow::OnWindowGUI(float dt)
{
}
EWindowType MainWindow::GetWindowType()
{
	return EWindowType::MainWindow;
}

