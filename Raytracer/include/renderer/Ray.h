/*
Representation of a ray. This is the foundation for the entire
renderer.
*/

#ifndef RT_RAY_H
#define RT_RAY_H

//#include <prims/Object.h>
#include <renderer/Point.h>
#include <renderer/Vector.h>

// Forward declaration
class Object;

class Ray {
	
public:
	Ray();
	Ray(Point p, Vector dir);

	// The ray's starting point
	Point origin;

	// The ray's directional vector
	Vector direction;

	// Pointer to object if ray was spawned inside an object
	// for refraction. NULL if ray is reflected or otherwise traversing
	// through the normal environment
	Object* spawnedInside;
};

#endif