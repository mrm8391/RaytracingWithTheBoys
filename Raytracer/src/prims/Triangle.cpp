
#include <prims/Triangle.h>
#include <renderer/Point.h>
#include <renderer/IntersectData.h>

Triangle::Triangle(Point p1, Point p2, Point p3) {
	this->p1 = Point(p1);
	this->p2 = Point(p2);
	this->p3 = Point(p3);
}

/*
Stub
*/
IntersectData Triangle::intersect(Ray ray)
{
	// barycentric to world conversion: u*p1 + v*p2 + w*p3

	// Vector wrapper class has dot and cross product functions already

	return IntersectData();
}

void Triangle::translate(double x, double y, double z) {

}

void Triangle::move(double x, double y, double z)
{
}
