/*
Sphere primitive
*/

#ifndef RT_SPHERE_H
#define RT_SPHERE_H

#include <prims/Object.h>
#include <renderer/IntersectData.h>

class Sphere : public Object {

public:

	double radius;

	/*
	Construct a sphere primitive at a position with radius r.
	*/
	Sphere(double x, double y, double z, double r);

	IntersectData intersect(Ray ray);
	void translate(double x, double y, double z);
	void move(double x, double y, double z);
};

#endif
