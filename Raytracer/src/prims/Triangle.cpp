
#include <prims/Triangle.h>
#include <renderer/Point.h>
#include <renderer/IntersectData.h>

Triangle::Triangle(Point p0, Point p1, Point p2) {
	this->p0 = Point(p0);
	this->p1 = Point(p1);
	this->p2 = Point(p2);
}

/*
Stub
*/
IntersectData Triangle::intersect(Ray ray)
{
	// barycentric to world conversion: u*p1 + v*p2 + w*p3

	// Vector wrapper class has dot and cross product functions already

	// Intersection Calculation
	// D = direction vector of ray

	// e1 = p1-p0
	Point e1(p1.subtract(p0));

	// e2 = p2-p0
	Point e2(p2.subtract(p0));

	// T = P0-p0
	Point T(ray.origin.subtract(p0));

	// P = D x e2
	Point P(ray.direction.cross(e2));

	// Q = T x e1
	Point Q(T.cross(e1));

	// Point preWuv = (Q*e2, P*T, Q*D)
	Point preWuv(
		Q.dot(e2),
		P.dot(T),
		Q.dot(ray.direction)
	);

	// Point (w, u, v) = 1/(P*e1) * preWuv
	double m = 1.0 / (P.dot(e1));

	Point wuv(
		m*preWuv.vec[0],
		m*preWuv.vec[1],
		m*preWuv.vec[2]
	);

	IntersectData intersect(1.0, 2.0, wuv);
	

	return IntersectData();
}

void Triangle::translate(double x, double y, double z) {

}

void Triangle::move(double x, double y, double z)
{
}
