﻿#pragma once
#include "Transform.h"
#include <iostream>
#include <map>

class PrimitiveModel
{
public:
	enum class PrimitiveType
	{
		Cube, //立方体
		Quad, //面片
		Sphere, // 球体
		Monkey, //猴头
	};
public:
	static Transform* CreatePrimitive(const PrimitiveType type);
	static std::map<PrimitiveType, Model*> cachedModel;

private:
	static Model* GetModel(PrimitiveType type);
};
