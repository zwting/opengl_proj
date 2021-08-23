//
// Created by zuowe on 2021/8/17.
//

#ifndef FANCY_ENGINE_SRC_GUI_SCENEWINDOW_H_
#define FANCY_ENGINE_SRC_GUI_SCENEWINDOW_H_

#include <glfw/glfw3.h>
#include "BaseWindow.h"

class SceneWindow: public BaseWindow
{
 protected:
	GLuint mTextureColor{};
 protected:
	void OnWindowGUI(float dt) override;
 public:
	void SetTextureColor(GLuint textureColor){mTextureColor = textureColor;}
	SceneWindow();
	EWindowType GetWindowType() override;
};

#endif //FANCY_ENGINE_SRC_GUI_SCENEWINDOW_H_
