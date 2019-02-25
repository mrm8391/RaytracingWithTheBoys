
#include <renderer/lighting/ShadingModel.h>
#include <renderer/lighting/LightSource.h>

ShadingModel::ShadingModel()
{
}

Vector ShadingModel::shade(LightSource light, Ray incoming, IntersectData inter)
{
	//Default, return material color.

	//Placeholder until material properties are implemented.
	//Will later be inter.object.color as a vector
	return Vector(inter.color,inter.color,inter.color);

}
