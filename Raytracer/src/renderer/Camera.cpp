
#include <vector>
#include <Eigen/Core>

#include <renderer/Camera.h>
#include <renderer/Point.h>
#include <renderer/Vector.h>
#include <prims/Object.h>
#include <utils/Transforms.h>
#include <renderer/World.h>

using Eigen::Vector4d;
using Eigen::Matrix4d;
using namespace std;

//Static runtime constant initialization

double Camera::SCREEN_WIDTH = 50.0;
double Camera::SCREEN_HEIGHT = 50.0;

unsigned int Camera::NUM_PIXELS_HORIZONTAL = 50;
unsigned int Camera::NUM_PIXELS_VERTICAL = 50;

double Camera::PIXEL_WIDTH = Camera::SCREEN_WIDTH / Camera::NUM_PIXELS_HORIZONTAL;
double Camera::PIXEL_HEIGHT = Camera::SCREEN_HEIGHT / Camera::NUM_PIXELS_VERTICAL;

double Camera::FOCAL_POINT = 5.0;

Camera::Camera(Point pos, Vector look, Vector base)
{
	objects = vector<Object>();
	screen = vector<vector<double>>();

	eyepoint = Point(pos);
	lookat = Vector(look);
	lookat.normalize();

	//Configure camera coordinate system.
	//Positive z-axis in direction of lookat
	//Positive y-axis in direction of up, above camera and orthogonal to lookat
	//Positive x-axis to right of camera, orthogonal to lookat and up

	n = Vector(lookat);
	v = n.cross(base);
	v.normalize();
	up = v.cross(n);
	up.normalize();
	u = Vector(up);
}

std::vector<std::vector<double>> Camera::render(World world)
{
	vector<vector<double>> pixels;


	//Nuke current object list, so it can be repopulated.
	//Do proper memory management if we use the heap later
	this->objects = vector<Object>();

	//Translation vector from world origin to camera position
	Vector dX = world.origin.subtract(eyepoint);

	//set view transform with v as X-axis, u/up as Y-axis, and n/lookat as Z-axis
	Matrix4d viewTransform = Transforms::viewTransform(v.vec, u.vec, n.vec, dX.vec);

	for (Object &obj : world.objects) {
		Object cameraObj = obj.transformAndCopy(viewTransform);

		this->objects.push_back(cameraObj);
	}

	/*
	RAYTRACING PLACEHOLDER
	RAYTRACING PLACEHOLDER
	RAYTRACING PLACEHOLDER
	RAYTRACING PLACEHOLDER
	RAYTRACING PLACEHOLDER
	RAYTRACING PLACEHOLDER
	*/

	//Set instance variables
	this->currentWorld = world;
	this->currentViewTransform = viewTransform;

	return pixels;
}
