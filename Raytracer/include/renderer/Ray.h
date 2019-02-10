/*
Representation of a ray. This is the foundation for the entire
renderer.
*/

#ifndef RT_RAY_H
#define RT_RAY_H

#include <renderer/Point.h>

class Ray {
	
public:
	Ray();

	// The ray's starting point
	Point origin;

	// The ray's directional vector
	Vector direction;
};

#endif