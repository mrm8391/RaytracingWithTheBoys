
#include <prims/Triangle.h>
#include <renderer/Point.h>
#include <renderer/IntersectData.h>
#include <iostream>

Triangle::Triangle(Point p0, Point p1, Point p2) {
	this->p0 = Point(p0);
	this->p1 = Point(p1);
	this->p2 = Point(p2);
}

IntersectData Triangle::intersect(Ray ray)
{
	// D = direction vector of ray (ray.direction)

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

	// Point (omega, u, v) = 1/(P*e1) * preWuv
	double divisor = P.dot(e1);
	
	// If P * e1 = 0, ray is parallel to triangle, and there is no intersection
	if (divisor == 0.0) {
		return IntersectData();
	}

	// Otherwise, ray is not parallel to triangle
	double m = 1.0 / divisor;

	// Calculate w, u, v
	double omega = m*preWuv.vec[0]; // w will be distance along ray of intersection point
	double u = m*preWuv.vec[1];
	double v = m*preWuv.vec[2];

	// u < 0, v < 0, u+v> 1, then intersection point is outside of triangle.
	if (u < 0.0 || v < 0.0 || (u + v) > 1.0) {
		return IntersectData();
	}

	// Calculate intersect in world coordinates from origin of ray, direction of ray, and distance along direction.
	Point worldCoordsIntersection(
		(omega * ray.direction.vec[0]) + ray.origin.vec[0],
		(omega * ray.direction.vec[1]) + ray.origin.vec[1],
		(omega * ray.direction.vec[2]) + ray.origin.vec[2]);

	// e1 x e2 gives the normal
	Vector normal = e1.cross(e2);
	normal.normalize();

	return IntersectData(omega, color, normal, this, worldCoordsIntersection);
}

void Triangle::translate(double x, double y, double z) {

}

void Triangle::move(double x, double y, double z)
{
}

void Triangle::transform(Eigen::Matrix4d matr)
{
	// Transform each point of the triangle
	p0.transform(matr);
	p1.transform(matr);
	p2.transform(matr);
}

Object * Triangle::copy()
{
	Triangle* t = new Triangle(*this);

	t->id = this->id;
	t->pos = this->pos;
	t->color = this->color;
	t->p0 = this->p0;
	t->p1 = this->p1;
	t->p2 = this->p2;

	return t;
}
