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

	Point p1, p2, p3;

	Triangle(Point p1, Point p2, Point p3);

	IntersectData intersect(Ray ray);
	void translate(double x, double y, double z);
	void move(double x, double y, double z);
};



#endif