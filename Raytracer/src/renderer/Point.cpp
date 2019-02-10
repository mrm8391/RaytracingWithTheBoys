#include <renderer/Point.h>
#include <renderer/Vector.h>

Point::Point() : Vector()
{
}

Point::Point(double x, double y, double z) : Vector(x,y,z)
{
}

Point::Point(Point &other) : Vector(other) {
	
}

Point::Point(Vector &other) : Vector(other) {

}

Vector Point::subtract(Point & other)
{
	double x = this->vec[0] - other.vec[0];
	double y = this->vec[1] - other.vec[1];
	double z = this->vec[2] - other.vec[2];

	return Vector(x,y,z);
}
