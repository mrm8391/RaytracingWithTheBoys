/*
Triangle primitive, defined in barycentric coordinates
*/

#ifndef RT_TRIANGLE_H
#define RT_TRIANGLE_H

#include <prims/Object.h>
#include <renderer/Point.h>
#include <renderer/IntersectData.h>

class Triangle : public Object {

public:

	Point p0, p1, p2;

	Triangle(Point p0, Point p1, Point p2);

	/*
	Calculates point of intersection, in world coordinates, of ray with triangle.
	Ray's direction may be normalized or not normalized, does not matter. 
		Returns NULL if there is no intersection between the ray and the triangle.
		Otherwise, returns pointer to single IntersectData instance with distance and color info.
	*/
	IntersectData* intersect(Ray ray);

	/*
	Translates all points of the triangle by x, y, and z. 
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
	Copy triangle, and transform it with a transformation matrix. New object will not have a unique ID, will
	have the ID of this object.

	@param matr Transformation matrix to apply to the object

	@return New, transformed version of current object. Transformed object will have the same ID.
	*/
	Object* transformAndCopy(Eigen::Matrix4d matr);
};



#endif