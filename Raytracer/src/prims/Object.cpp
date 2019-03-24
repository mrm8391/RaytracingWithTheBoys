#include <prims/Object.h>

Object::Object() : Object(0,0,0)
{
	
}

//Note: ShadingModel parameter defaults to PhongShading in Object.h
Object::Object(double x, double y, double z, ShadingModel shad) {
	this->id = 0;
	this->pos = Point(x, y, z);
	this->color = Vector(0.0,0.0,0.0);

	PhongShading* p = new PhongShading();
	this->shadingModel = p;
	//this->shadingModel = shad;
}

IntersectData Object::intersect(Ray ray)
{
	return IntersectData();
}

Vector Object::shade(LightSource light, Ray incoming, IntersectData inter)
{
	return this->shadingModel->shade(light, incoming, inter);
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
