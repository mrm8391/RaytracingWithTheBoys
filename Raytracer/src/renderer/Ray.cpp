#include <renderer/Ray.h>
#include <renderer/Point.h>
#include <renderer/Vector.h>

Ray::Ray() : Ray(Point(0,0,0), Vector(0,0,0))
{
}

Ray::Ray(Point p, Vector dir)
{
	this->origin = Point(p);
	this->direction = Vector(dir);
	this->insideObject = 0;
}
