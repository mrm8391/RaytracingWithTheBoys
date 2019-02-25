/*
Phong shading model
*/

#ifndef RT_PHONG_H
#define RT_PHONG_H

#include <renderer/lighting/LightSource.h>
#include <renderer/Vector.h>
#include <renderer/IntersectData.h>
#include <renderer/Ray.h>
#include <renderer/lighting/ShadingModel.h>

class PhongShading : public ShadingModel{

public:
	PhongShading();

	/*
	Compute phong shading on surface.

	@param light - Light source to base illumination off of
	@param incoming - Incoming ray that caused the intersection, used for reflection
	@param inter - Intersection data, containing object data and intersection point

	@return Radiance triple of resulting light after applying shading
	*/
	Vector shade(LightSource light, Ray incoming, IntersectData inter);

};

#endif