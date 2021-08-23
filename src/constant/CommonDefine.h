//
// Created by zuowe on 2021/8/17.
//

#ifndef FANCY_ENGINE_SRC_CONSTANT_COMMONDEFINE_H_
#define FANCY_ENGINE_SRC_CONSTANT_COMMONDEFINE_H_
#include <functional>

enum class EWindowType{
	MainWindow = 1,
	SceneWindow = 2,
	HierarchyWindow = 3,
	InspectorWindow = 4,
};


enum class EEventType: unsigned {
	SceneViewSizeChanged = 1
};

typedef std::function<void (EEventType, void*)> EventHandler;

#endif //FANCY_ENGINE_SRC_CONSTANT_COMMONDEFINE_H_
