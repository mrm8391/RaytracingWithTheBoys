/*
Representation of a point location. Same representation as a vector but with different operations
*/

#ifndef RT_POINT_H
#define RT_POINT_H

#include "Vector.h"

class Point : public Vector {

public:
	Point();
	Point(double x, double y, double z);
	Point(Vector &other);

	//Copy constructor
	Point(Point &other);

	// Returns a Vector with the values of (this.x - other.x, this.y - other.y, this.z - other.z)
	Vector subtract(Point &other);

	void transform(Eigen::Matrix4d matr);

};

#endif

