
#include <prims/Triangle.h>
#include <renderer/Point.h>
#include <renderer/IntersectData.h>
#include <iostream>

Triangle::Triangle(Point p0, Point p1, Point p2) {
	this->p0 = Point(p0);
	this->p1 = Point(p1);
	this->p2 = Point(p2);
}

/*
Calculates point of intersection, in world coordinates, of ray with triangle. 
	Returns NULL if there is no intersection between the ray and the triangle.
	Otherwise, returns pointer to single IntersectData instance with distance and color info. 
*/
IntersectData* Triangle::intersect(Ray ray)
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

	// Point (w, u, v) = 1/(P*e1) * preWuv
	double divisor = P.dot(e1);
	
	// If P * e1 = 0, ray is parallel to triangle, and there is no intersection
	if (divisor == 0.0) {
		return NULL;
	}

	// Otherwise, ray is not parallel to triangle
	double m = 1.0 / divisor;

	// Calculate w, u, v
	double w = m*preWuv.vec[0]; // w will be distance along ray of intersection point
	double u = m*preWuv.vec[1];
	double v = m*preWuv.vec[2];

	// u < 0, v < 0, u+v> 1, then intersection point is outside of triangle.
	if (u < 0.0 && v < 0.0 && (u + v) > 1.0) {
		return NULL;
	}

	// barycentric to world conversion: u*p0 + v*p1 + w*p2
	Point worldCoordsIntersection(
		u*p0.vec[0] + v*p1.vec[0] + w*p2.vec[0],
		u*p0.vec[1] + v*p1.vec[1] + w*p2.vec[1],
		u*p0.vec[2] + v*p1.vec[2] + w*p2.vec[2]
	);

	// STAND-IN
	double color = 0.5;

	// If needed in future: e1 x e2 gives the normal
	IntersectData intersect(w, color, worldCoordsIntersection);

	return &intersect;
}

void Triangle::translate(double x, double y, double z) {

}

void Triangle::move(double x, double y, double z)
{
}
