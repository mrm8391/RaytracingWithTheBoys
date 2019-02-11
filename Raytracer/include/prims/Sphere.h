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

	/*
	Transform current object by an arbitrary transformation matrix, typically a view transform.

	@param matr Transformation matrix to apply to the object
	*/
	void transform(Eigen::Matrix4d matr);

	/*
	Copy sphere, and transform it with a transformation matrix. New object will not have a unique ID, will
	have the ID of this object.

	@param matr Transformation matrix to apply to the object

	@return New, transformed version of current object. Transformed object will have the same ID.
	*/
	Object* transformAndCopy(Eigen::Matrix4d matr);
};

#endif
