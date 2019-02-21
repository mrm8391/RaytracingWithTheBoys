#include <prims/Object.h>

unsigned int Object::NEXT_ID = 0;

Object::Object() : Object(0,0,0)
{
	
}

Object::Object(double x, double y, double z) {
	this->id = Object::NEXT_ID;
	Object::NEXT_ID++;

	this->pos = Point(x, y, z);
	this->color = 0.0;
}

IntersectData Object::intersect(Ray ray)
{
	return IntersectData();
}

void Object::translate(double x, double y, double z)
{
}

void Object::move(double x, double y, double z)
{
}

void Object::transform(Eigen::Matrix4d matr)
{
}

Object * Object::copy()
{
	return nullptr;
}
