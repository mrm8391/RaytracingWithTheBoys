#include <prims/Sphere.h>
#include <renderer/IntersectData.h>

Sphere::Sphere(double x, double y, double z, double r)
{
	this->pos = Point(x, y, z);
	this->radius = r;
}

IntersectData Sphere::intersect(Ray ray)
{
	return IntersectData();
}

void Sphere::translate(double x, double y, double z)
{
}

void Sphere::move(double x, double y, double z)
{
}
