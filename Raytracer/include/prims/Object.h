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

	// For now, a 0-1 value
	double color;

	Object();

	// Returns array of intersections with that object
	virtual IntersectData* intersect(Ray ray) = 0;

	virtual void translate(double x, double y, double z) = 0;

	virtual void move(double x, double y, double z) = 0;
};

#endif