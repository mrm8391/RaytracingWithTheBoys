/*
Base class for lighting model of a material.

Will be used for computing lighting of a surface.
*/

#ifndef RT_SHADING_H
#define RT_SHADING_H

#include <renderer/lighting/LightSource.h>
#include <renderer/Vector.h>
#include <renderer/IntersectData.h>
#include <renderer/Ray.h>

class ShadingModel {

public:
	ShadingModel();

	/*
	Virtual base method to compute shading based off of intersection and light.
	Object material properties will be accessible in IntersectData.
	This computation assumes that the incoming ray is not a shadow ray,
	and that the ray successfully reaches the light.

	Default base method merely returns the object's color.

	@param light - Light source to base illumination off of
	@param incoming - Incoming ray that caused the intersection, used for reflection
	@param inter - Intersection data, containing object data and intersection point

	@return Radiance triple of resulting light after applying shading
	*/

	virtual Vector shade(LightSource light, Ray incoming, IntersectData inter);

};

#endif