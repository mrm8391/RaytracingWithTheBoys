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

	//
	// Phong constants
	//

	// ambient constant
	double ka;
	// diffuse constant
	double kd; 
	// specular constant
	double ks;
	// specular exponent
	double ke;

	//
	// Ray constants
	//

	// reflection constant
	double kr;
	// transmittion constant
	double kt;
	// index of refraction
	double n;

	// Color of specular highlight
	Vector specColor;

	void setPhong(double a, double d, double s, double e);

	// Returns color
	virtual Vector colorAtUV(double u, double v);

	void setReflective(double r, double t);
};

#endif