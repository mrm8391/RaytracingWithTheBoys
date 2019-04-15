/*
Placeholder for a vector object. May be replaced with a library in the future.
*/

#ifndef RT_VECTOR_H
#define RT_VECTOR_H

#include <Eigen/Core>

class Vector {

public:
	Vector();
	Vector(double x, double y, double z);

	//Copy constructor
	Vector(const Vector &other);

	void normalize();

	//Return dot product of the two vectors
	double dot(Vector other);

	//Return new vector that is the cross product of the two vectors
	Vector cross(Vector other);

	//Return new vector that is perfectly reflected over a surface orthogonal to a normal.
	//Assumes this and normal are normalized.
	//
	//@param normal Normal of surface reflecting across
	//
	//@return Newly constructed reflected vector
	Vector reflect(Vector normal);

	//Return new vector refracted through a surface orthogonal to a normal.
	//Assumes this and normal are normalized.
	//
	//@param normal Normal of surface refracting through
	//@param ni Snell's law index of refraction for source medium
	//@param nt Snell's law index of refraction for target medium transmitted to
	//
	//@return Newly constructed refracted vector
	Vector refract(Vector normal, double ni, double nt);

	//Return new vector that is scaled by a double. Can be used to flip a vector to be backwards
	Vector scale(double value);

	//Return new vector resulting from subtraction.
	//Different from point subtraction; this is an actual vector subtraction.
	Vector subtract(Vector other);

	//Return new vector resulting from addition.
	Vector add(Vector other);

	Eigen::Vector3d vec;
};

#endif

