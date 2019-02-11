/*
Representation of a ray. This is the foundation for the entire
renderer.
*/

#ifndef RT_RAY_H
#define RT_RAY_H

#include <renderer/Point.h>
#include <renderer/Vector.h>

class Ray {
	
public:
	Ray();
	Ray(Point p, Vector dir);

	// The ray's starting point
	Point origin;

	// The ray's directional vector
	Vector direction;
};

#endif