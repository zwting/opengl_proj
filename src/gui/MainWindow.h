//
// Created by zuowe on 2021/8/16.
//

#ifndef FANCY_ENGINE_SRC_GUI_MAINWINDOW_H_
#define FANCY_ENGINE_SRC_GUI_MAINWINDOW_H_

#include <imgui.h>
#include "BaseWindow.h"

class MainWindow: public BaseWindow
{
 public:
	MainWindow(int width, int height);
	void OnWindowGUI(float dt) override;
};

#endif //FANCY_ENGINE_SRC_GUI_MAINWINDOW_H_
