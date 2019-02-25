/*
Representation of a point light source.
*/

#ifndef RT_LIGHT_H
#define RT_LIGHT_H

#include <renderer/Vector.h>
#include <renderer/Point.h>

class LightSource {

public:

	//3 component triple of R, G, and B radiance
	Vector radiance;

	//Position of light source
	Point pos;

	LightSource();

	LightSource(Point position, double redRad, double greenRad, double blueRad);



};

#endif