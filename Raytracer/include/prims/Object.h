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

	virtual IntersectData intersect(Ray ray) = 0;
	virtual void translate(double x, double y, double z) = 0;
	virtual void move(double x, double y, double z) = 0;
};

#endif