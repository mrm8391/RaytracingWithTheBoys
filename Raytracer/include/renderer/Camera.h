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

//Camera runtime constants
public:	

	//Virtual screen width, in units of world coordinates
	static double SCREEN_WIDTH, SCREEN_HEIGHT;

	//Virtual screen resolution, in number of pixels
	static unsigned int NUM_PIXELS_HORIZONTAL, NUM_PIXELS_VERTICAL;

	//Width and height of pixels in units of world coordinates.
	//Derived from screen width and # pixels
	static double PIXEL_WIDTH, PIXEL_HEIGHT;

	//Distance from camera to virtual screen ("Focal point")
	static double FOCAL_POINT;


//Instance variables and methods
public:

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

	//Virtual screen in front of camera.
	//Placeholder; will contain colors, and later irradiance
	std::vector<std::vector<double>> screen;

	//Reference to most recent world rendered by camera.
	//Uninitialized until first render() call
	World currentWorld;

	//Transformation matrix to transform a point from world space to camera space.
	//Uninitialized until first render() call
	Eigen::Matrix4d currentViewTransform;

	/*
	Construct a camera and coordinate system from given variables.

	@param pos Point location of the camera
	@param look Direction camera is pointing at
	@param base Arbitrary vector to base coordinate system off of (NOT up).
				Will be used to compute unit vector v, which will be used
				to compute the up vector. Can be the same as up, but not necessary.
	*/
	Camera(Point pos, Vector look, Vector base);

	/*
	Render a world from the perspective of the camera.
	Will populate camera's object list with world objects transformed to camera space,
	trace rays to the objects, and return a 2D list of colors (currently, only grayscale intensities).

	@param world The world object to render

	@return 2D stl vector of pixel intensities
	*/
	std::vector<std::vector<double>> render(World world);
};

#endif