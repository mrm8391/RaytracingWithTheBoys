#include "..\..\..\include\renderer\materials\SolidMaterial.h"

// Specul (the specular highlight color) defaults to 1.0 in SolidMaterial.h
SolidMaterial::SolidMaterial(Vector col, double a, double d, double s, double e, Vector specul) : Material(a, d, s, e, specul) {
	this->color = col;
}

Vector SolidMaterial::colorAtUV(double u, double v) {
	return this->color;
}
