#include <renderer/Vector.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

using Eigen::Vector3d;

Vector::Vector() : Vector(0,0,0)
{
	
}

Vector::Vector(double x, double y, double z) {
	this->vec = Vector3d();
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
}

Vector::Vector(Vector &other) : Vector(other.vec[0], other.vec[1], other.vec[2]) {

}

void Vector::normalize()
{
	this->vec.normalize();
}

double Vector::dot(Vector other)
{
	return this->vec.dot(other.vec);
}

Vector Vector::cross(Vector other)
{
	Vector3d result = this->vec.cross(other.vec);
	return Vector(result[0], result[1], result[2]);
}
