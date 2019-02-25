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
	Vector(Vector &other);

	void normalize();

	//Return dot product of the two vectors
	double dot(Vector other);

	//Return new vector that is the cross product of the two vectors
	Vector cross(Vector other);

	//Return new vector that is reflected across a normal vector.
	//Assumes normal vector is normalized already.
	Vector reflect(Vector normal);

	//Return new vector that is scaled by a double. Can be used to flip a vector to be backwards
	Vector scale(double value);

	//Return new vector resulting from subtraction.
	//Different from point subtraction; this is an actual vector subtraction.
	Vector subtract(Vector other);

	Eigen::Vector3d vec;
};

#endif

