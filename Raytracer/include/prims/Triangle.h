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
	Calculates intersection point with a ray. 
	*/
	IntersectData intersect(Ray ray);

	/*
	Translates all points of the triangle by x, y, and z. 
	*/
	void translate(double x, double y, double z);

	/*
	Moves the triangle to (x,y,z), regardless of triangle's current position. 
	*/
	void move(double x, double y, double z);
};



#endif