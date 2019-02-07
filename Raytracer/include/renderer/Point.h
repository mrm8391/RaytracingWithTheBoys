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

	//Copy constructor
	Point(Point &other);
};

#endif

