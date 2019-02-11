#include <renderer/Ray.h>
#include <renderer/Point.h>
#include <renderer/Vector.h>

Ray::Ray()
{
}

Ray::Ray(Point p, Vector dir)
{
	this->origin = Point(p);
	this->direction = Vector(dir);
}
