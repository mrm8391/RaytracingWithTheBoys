/*
Sphere primitive
*/

#ifndef RT_SPHERE_H
#define RT_SPHERE_H

#include <prims/Object.h>
#include <renderer/IntersectData.h>

class Sphere : public Object {

public:
	Sphere();

	Sphere(Point c, double r) {
		pos = c;
		radius = r;
	}

	double radius;

	/*
	Calculates points of intersection, in world coordinates, of ray with sphere.
	Ray's direction MUST BE NORMALIZED
	*/
	std::vector<IntersectData> intersect(Ray ray);

	/*
	Translates center point of the sphere by x, y, and z.
	*/
	void translate(double x, double y, double z);

	/*
	Moves the triangle to (x,y,z), regardless of triangle's current position.
	*/
	void move(double x, double y, double z);

	/*
	Transform current object by an arbitrary transformation matrix, typically a view transform.

	@param matr Transformation matrix to apply to the object
	*/
	void transform(Eigen::Matrix4d matr);

	Object* copy();
};

#endif
