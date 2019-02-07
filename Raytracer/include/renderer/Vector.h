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

	Eigen::Vector3d vec;
};

#endif

