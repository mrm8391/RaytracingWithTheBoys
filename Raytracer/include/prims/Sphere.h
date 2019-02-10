/*
Sphere primitive
*/

#ifndef RT_SPHERE_H
#define RT_SPHERE_H

#include "Object.h"

class Sphere : public Object {

public:
	Sphere();

	Sphere(Point c, double r) : center(c), radius(r) {};

	Point center;

	double radius;

	/*
	Calculates points of intersection, in world coordinates, of ray with sphere.
	Ray's direction MUST BE NORMALIZED
		Returns NULL if there is no intersection between the ray and the sphere.
		Otherwise, returns pointer to beginning of IntersectData array.
	*/
	IntersectData* intersect(Ray ray);

	/*
	Translates center point of the sphere by x, y, and z.
	*/
	void translate(double x, double y, double z);

	/*
	Moves the triangle to (x,y,z), regardless of triangle's current position.
	*/
	void move(double x, double y, double z);
};

#endif
