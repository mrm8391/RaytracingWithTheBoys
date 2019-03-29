/*
Solid Phong material
*/

#ifndef RT_SOLID_H
#define RT_SOLID_H

#include <renderer/materials/Material.h>

class SolidMaterial : public Material {

public:
	SolidMaterial(Vector col, double a, double d, double s, double e, Vector specul = Vector(1.0,1.0,1.0));

	Vector color;

	// Returns this->color
	Vector colorAtUV(double u, double v);
};

#endif
