/*
Base-level material class, containing Phong constants
*/

#include <renderer/Vector.h>

#ifndef RT_MATERIAL_H
#define RT_MATERIAL_H

class Material {

public:
	// Default constructor
	Material();

	Material(double a, double d, double s, double e, Vector specular = Vector(1.0,1.0,1.0));

	// Phong constants
	// ambient constant
	double ka;
	// diffuse constant
	double kd; 
	// specular constant
	double ks;
	// specular exponent
	double ke;

	// Color of specular highlight
	Vector specColor;

	// Returns color
	virtual Vector colorAtUV(double u, double v);

};

#endif