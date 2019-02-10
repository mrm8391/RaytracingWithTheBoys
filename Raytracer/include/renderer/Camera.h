/*
Camera object, for defining the viewing perspective.
*/

#ifndef RT_CAMERA_H
#define RT_CAMERA_H

#include <vector>
#include <Eigen/Core>

#include <renderer/Point.h>
#include <renderer/Vector.h>
#include <prims/Object.h>
#include <renderer/World.h>

class Camera {

public:
	/*
	Construct a camera and coordinate system from given variables.

	@param pos Point location of the camera
	@param look Direction camera is pointing at
	@param base Arbitrary vector to base coordinate system off of (NOT up).
				Will be used to compute unit vector v, which will be used
				to compute the up vector. Can be the same as up, but not necessary.
	*/
	Camera(Point pos, Vector look, Vector base, World w);

	//Copy of world objects transformed to camera space
	std::vector<Object> objects;

	//Camera position, in world coordinates
	Point eyepoint;

	//Direction camera is pointing at, in world coordinates
	Vector lookat;

	//Camera up vector, in world coordinates
	Vector up;

	//Unit vectors defining camera coordinate space.
	//n is analogous to lookat, u to up, and v is orthogonal to both
	Vector n, u, v;

	//Transformation matrix to transform a point from world space to camera space
	Eigen::Matrix4d viewtransform;

	//Virtual screen in front of camera.
	//Placeholder; will contain colors, and later irradiance
	std::vector<std::vector<double>> screen;

	World world;
};

#endif