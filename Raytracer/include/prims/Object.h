/*
Abstract base class for primitive objects that can be placed in the scene.

These will be mathematically defined.
*/

#ifndef RT_OBJECT_H
#define RT_OBJECT_H

#include <vector>

#include <renderer/Point.h>
#include <renderer/Ray.h>
#include <renderer/IntersectData.h>

class Object {

public:
	Point pos;

	Object();

	// Returns array of intersections with that object
	virtual IntersectData* intersect(Ray ray);

	virtual void translate(double x, double y, double z);

	virtual void move(double x, double y, double z);
};

#endif