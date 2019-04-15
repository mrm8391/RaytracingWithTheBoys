#include <prims/Sphere.h>
#include <algorithm>

using namespace std;

Sphere::Sphere() : Object()
{
}

vector<IntersectData> Sphere::intersect(Ray ray)
{
	vector<IntersectData> intersections;

	double dx = ray.direction.vec[0];
	double dy = ray.direction.vec[1];
	double dz = ray.direction.vec[2];

	double x0 = ray.origin.vec[0];
	double y0 = ray.origin.vec[1];
	double z0 = ray.origin.vec[2];

	double xC = pos.vec[0];
	double yC = pos.vec[1];
	double zC = pos.vec[2];

	// B = 2*(dx(x0-xC) + dy(y0-yC) + dz(z0-zC))
	double B = 2 * (
			dx * (x0 - xC) +
			dy * (y0 - yC) +
			dz * (z0 - zC));

	// C = (x0-xC)^2 + (y0-yC)^2 + (z0-zC)^2 - r^2
	double C =
		pow((x0 - xC),2.0) +
		pow((y0 - yC), 2.0) +
		pow((z0 - zC), 2.0) -
		pow(radius, 2.0);

	// omega is calculated via quadratic function, and is used to find intersection point.
	double omegaA, omegaB;
	bool twoIntersections = true;

	// Discriminant of quadratic equation: (B^2) - 4C
	double discriminant = pow(B, 2.0) - 4 * C;
	 
	if (discriminant < 0.0) {
		// ((B^2) - 4C < 0): no intersection
		return intersections;
	}
	else if (discriminant == 0.0) {
		// ((B^2) - 4C = 0): ray intersects at sphere's surface
		omegaA = -B / 2.0;
		twoIntersections = false;
	}
	else {
		// ((B^2) - 4C > 0): ray goes through sphere. Use least positive root for ((B^2) - 4C)^.5
		omegaA = (-B + sqrt(discriminant)) / 2.0;
		omegaB = (-B - sqrt(discriminant)) / 2.0;

		//omega = std::min(omegaA, omegaB);
	}

	// Calculate point based on the omega of closest point
	Point worldCoordsIntersectionA(
		x0 + (dx * omegaA),
		y0 + (dy * omegaA),
		z0 + (dz * omegaA));

	// Normal vector: (x, y, z) = (xi–xc), (yi–yc), (zi–zc)) normalized, where xi, yi, and zi are intersection coords
	Vector normalA(
		worldCoordsIntersectionA.vec[0] - xC,
		worldCoordsIntersectionA.vec[1] - yC,
		worldCoordsIntersectionA.vec[2] - zC);

	normalA.normalize();

	IntersectData interA(omegaA, normalA, this, worldCoordsIntersectionA);
	intersections.push_back(interA);

	//now do the same calculations for intersection B if there exists one
	if (twoIntersections) {
		Point worldCoordsIntersectionB(
			x0 + (dx * omegaB),
			y0 + (dy * omegaB),
			z0 + (dz * omegaB));

		Vector normalB(
			worldCoordsIntersectionB.vec[0] - xC,
			worldCoordsIntersectionB.vec[1] - yC,
			worldCoordsIntersectionB.vec[2] - zC);

		normalB.normalize();

		IntersectData interB(omegaB, normalB, this, worldCoordsIntersectionB);
		intersections.push_back(interB);
	}

	return intersections;
}

void Sphere::translate(double x, double y, double z)
{
}

void Sphere::move(double x, double y, double z)
{
}

void Sphere::transform(Eigen::Matrix4d matr)
{
	// All we need to do is transform the point
	pos.transform(matr);
}

Object * Sphere::copy()
{
	Sphere* s = new Sphere(*this);

	s->id = this->id;
	s->pos = Point(this->pos);
	s->outerMaterial = this->outerMaterial;
	s->radius = this->radius;

	return s;
}



