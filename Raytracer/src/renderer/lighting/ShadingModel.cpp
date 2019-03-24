
#include <renderer/lighting/ShadingModel.h>
#include <renderer/lighting/LightSource.h>
#include <prims/Object.h>

ShadingModel::ShadingModel()
{
}

Vector ShadingModel::shade(LightSource light, Ray incoming, IntersectData inter)
{
	//Default, return material color.
	return inter.intersectedObject->color;
}
