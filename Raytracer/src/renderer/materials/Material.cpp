#include <renderer/materials/Material.h>

Material::Material() {
}

// Note: specular defaults to Vector(1.0,1.0,1.0) for white-colored highlights in Material.h
Material::Material(double a, double d, double s, double e, Vector specular) {
	this->ka = a;
	this->kd = d;
	this->ks = s;
	this->ke = e;

	this->specColor = specular;
}

// Defaults to white
Vector Material::colorAtUV(double u, double v)
{
	return Vector(1.0,1.0,1.0);
}
