
#include <renderer/lighting/PhongShading.h>
#include <algorithm>
#include <prims/Object.h>

PhongShading::PhongShading()
{
}

Vector PhongShading::shade(LightSource light, Ray incoming, IntersectData inter)
{
	//inter.intersectedObject->shade();
	Vector objColor = inter.intersectedObject->color;
	Vector specColor = Vector(1.0,1.0,1.0);

	//placeholders, grab from material
	double ka = 0.6, kd = 0.5, ks = 0.4, ke = 0.6;

	Point I = inter.intersection;

	//placeholder. Will be object.normal(inter.intersection)
	Vector N = inter.normal;

	// Vector from light to inter
	Vector S = I.subtract(light.pos);

	// Perfectly reflected light direction
	Vector R = S.reflect(N);

	// Vector from intersection to viewpoint/ray origin
	Vector V = incoming.origin.subtract(I);

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

		double res = ambient + diffuse + specular;

		outputRadiance.vec[i] = res;
	}

	return outputRadiance;
}
