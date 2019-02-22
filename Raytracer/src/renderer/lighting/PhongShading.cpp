
#include <renderer/lighting/PhongShading.h>

PhongShading::PhongShading()
{
}

Vector PhongShading::shade(LightSource light, Ray incoming, IntersectData inter)
{
	// WIP

	Point I = inter.intersection;

	Vector N = Vector(); //placeholder

	Vector S = light.pos.subtract(I);

	Vector V = incoming.origin.subtract(I);

	return Vector();
}
