#include <prims/Sphere.h>
#include <algorithm>

Sphere::Sphere() : Object()
{
}

IntersectData Sphere::intersect(Ray ray)
{
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
	double omega;

	// Discriminant of quadratic equation: (B^2) - 4C
	double discriminant = pow(B, 2.0) - 4 * C;
	 
	if (discriminant < 0.0) {
		// ((B^2) - 4C < 0): no intersection
		return IntersectData();
	}
	else if (discriminant == 0.0) {
		// ((B^2) - 4C = 0): ray intersects at sphere's surface
		omega = -B / 2.0;
	}
	else {
		// ((B^2) - 4C > 0): ray goes through sphere. Use least positive root for ((B^2) - 4C)^.5
		double omegaA = (-B + sqrt(discriminant)) / 2.0;
		double omegaB = (-B - sqrt(discriminant)) / 2.0;

		omega = std::min(omegaA, omegaB);
	}

	// Calculate point based on the omega of closest point
	Point worldCoordsIntersection(
		x0 + (dx * omega),
		y0 + (dy * omega),
		z0 + (dz * omega));

	// How to calculate normal is on slides
	return IntersectData(omega, color, worldCoordsIntersection);
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
	s->color = this->color;
	s->radius = this->radius;

	return s;
}



