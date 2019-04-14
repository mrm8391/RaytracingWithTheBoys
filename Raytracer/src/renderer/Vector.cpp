#include <renderer/Vector.h>

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <algorithm>

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

Vector::Vector(const Vector &other) : Vector(other.vec[0], other.vec[1], other.vec[2]) {

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

Vector Vector::reflect(Vector normal)
{
	//d=this
	//r = d - 2(2*n)n

	double dprod = this->dot(normal);

	Vector scaledNorm = normal.scale(2 * dprod);

	Vector res = this->subtract(scaledNorm);

	return res;
}

Vector Vector::refract(Vector normal, double ni, double nt)
{
	//screwy math, d=this
	//t = ( ni * (d - n(d DOT n)) / nt ) 
	//   + n * sqrt(1 - ( ni^2 * (1 - (d DOT n)^2 ) / nt^2 )

	normal = normal.scale(-1);

	double dprod = this->dot(normal);

	double rootComponent = 1.0 - 
		(
			(pow(ni, 2) * (1.0 - pow(dprod, 2))) / 
			(pow(nt, 2))
		);

	// Total internal reflection check. If root component negative, 
	// transmissive ray goes in reflected direction instead.
	if (rootComponent < 0.0) {
		return this->reflect(normal);
	}

	Vector rootVector = normal.scale(sqrt(rootComponent));

	double snellComponent = (ni / nt);
	
	Vector temp1 = normal.scale(dprod);
	Vector temp2 = this->subtract(temp1);
	Vector firstVector = temp2.scale(snellComponent);

	Vector res = firstVector.add(rootVector);

	return res;
}

Vector Vector::scale(double value)
{
	return Vector(this->vec[0]*value, this->vec[1] * value, this->vec[2] * value);
}

Vector Vector::subtract(Vector other)
{
	Vector3d res = this->vec - other.vec;

	return Vector(res[0], res[1], res[2]);
}

Vector Vector::add(Vector other)
{
	Vector3d res = this->vec + other.vec;

	return Vector(res[0], res[1], res[2]);
}
