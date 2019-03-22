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

	// LightSource's id, for use by the world/camera
	int id;

	LightSource();

	LightSource(Point position, double redRad, double greenRad, double blueRad);

	LightSource* copy();

	/*
	Transform object by an arbitrary transformation matrix, typically a view transform.
	Modifies current light source.

	@param matr Transformation matrix to apply to the light source's position
	*/
	void transform(Eigen::Matrix4d matr);



};

#endif