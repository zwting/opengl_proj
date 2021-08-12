#include "PrimitiveModel.h"

std::map<PrimitiveModel::PrimitiveType, Model*> PrimitiveModel::cachedModel;

Node* PrimitiveModel::CreatePrimitive(const PrimitiveType type)
{
	Node* ret = nullptr;
	ret = new Node(VEC3_ZERO, QUA_IDENTITY);
	ret->SetModel(GetModel(type));

	return ret;
}

Model* PrimitiveModel::GetModel(PrimitiveType type)
{
	if (cachedModel[type]) return cachedModel[type];

	switch (type)
	{
	case PrimitiveType::Cube:
		{
			Model* model = new Model("res/model/cube.obj");
			cachedModel[type] = model;
			break;
		}
	case PrimitiveType::Quad:
		{
			Model* model = new Model("res/model/quad.obj");
			cachedModel[type] = model;
			break;
		}
	case PrimitiveType::Sphere:
		{
			Model* model = new Model("res/model/sphere.obj");
			cachedModel[type] = model;
		break;
		}
	case PrimitiveType::Monkey:
		{
			Model* model = new Model("res/model/houtou.obj");
			cachedModel[type] = model;
			break;
		}
	default:
		return cachedModel[PrimitiveType::Cube];
	}

	return cachedModel[type];
}
