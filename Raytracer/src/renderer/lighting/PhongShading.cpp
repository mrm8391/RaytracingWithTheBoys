
#include <renderer/lighting/PhongShading.h>
#include <algorithm>
#include <prims/Object.h>
#include <iostream>

PhongShading::PhongShading()
{
}

Vector PhongShading::shade(LightSource light, Ray incoming, IntersectData inter)
{
	Vector objColor = inter.intersectedObject->color;
	Vector specColor = Vector(1.0,1.0,1.0);

	//placeholders, grab from material
	double ka = 0.8, kd = 0.5, ks = 0.4, ke = 2.0;

	Point I = inter.intersection;

	// Normal off of surface
	Vector N = inter.normal;

	// Vector from inter to light
	Vector S = light.pos.subtract(I);

	N.normalize();
	S.normalize();

	// Perfectly reflected light direction
	Vector R = S.reflect(N);

	// Vector from intersection to viewpoint/ray origin
	Vector V = incoming.origin.subtract(I);

	//std::cout << "R: [" << R.vec[0] << ", " << R.vec[1] << ", " << R.vec[2] << "]   ";
	//std::cout << "V: [" << V.vec[0] << ", " << V.vec[1] << ", " << V.vec[2] << "]\n";
	// Just to be safe
	S.normalize();
	R.normalize();
	V.normalize();

	double diffuseDot = S.dot(N);
	double specularDot = R.dot(V);

	Vector outputRadiance;

	//Compute phong reflected radiance for each RGB component.
	for (int i = 0; i < 3; i++) {
		double ambient = ka * objColor.vec[i] * light.radiance.vec[i];

		// diffuseDot = S dot N
		double diffuse = kd * light.radiance.vec[i] * objColor.vec[i] * diffuseDot;

		// specularDot = R dot V
		double specular = ks * light.radiance.vec[i] * specColor.vec[i] * pow(specularDot, ke);
		//std::cout << "light.radiance.vec[i]: " << light.radiance.vec[i] << ", specularDot: " << specularDot << "\n";

		double res = ambient + diffuse + specular;
		//std::cout << "ambient: " << ambient << ", diffuse: " << diffuse << ", specular: " << specular << "\n";
		outputRadiance.vec[i] = res;
	}

	return outputRadiance;
}
