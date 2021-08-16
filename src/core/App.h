//
// Created by zwt on 2020/3/10.
//

#ifndef CMAKE_LEARN_APP_H
#define CMAKE_LEARN_APP_H

#include <glfw/glfw3.h>
#include <design/Singleton.h>
#include "Input.h"
#include "gui/SceneWindow.h"
#include <iostream>

class App : public Singleton<App>
{
private:
	GLFWwindow* mWindow;
	int mWidth;
	int mHeight;
	int mFps;
	const char* mTitle;
	int mIsInitFinished;
	GLuint mFBO;
	GLuint mTextureColorBuffer;
	GLuint mRBO;
	SceneWindow* mSceneWindow;
private:
	//=================回调方法==================
	/**
	 * 错误回调
	 * @param error
	 * @param description
	 */
	static void ErrorCallback(int error, const char* description);

private:
	//=====================内部回调方法======================
	/**
	 * 初始化各种回调方法
	 */
	void SetupCallbacks();
private:
	//======================构造方法=========================
SINGLETON(App)
public:
	//=====================getter setter=====================
	GLFWwindow* window();
	int GetWidth() const;
	int GetHeight() const;
	int GetFPS() const;
	const char* GetTitle() const;
	int InitComplete() const;

public:
	//======================对外接口======================
	bool Init(const char* title, int width, int height);
	void Run();
protected:
	//=======================内部方法=======================
	void Update(const double dt);
	void RenderGUI(double dt);
	void Render(const double dt);
	void ImGUIBackendInit(GLFWwindow* window, const char* glsl_version);
	void InitLogicTmp();
	void InitFBO();
	void Clear();
	void InitWindows();
};

//创建单例
//SINGLETON(App)
#endif //CMAKE_LEARN_APP_H
