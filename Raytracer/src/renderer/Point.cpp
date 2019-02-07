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