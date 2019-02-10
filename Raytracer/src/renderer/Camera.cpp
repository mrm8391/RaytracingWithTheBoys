
#include <vector>
#include <Eigen/Core>

#include <renderer/Camera.h>
#include <renderer/Point.h>
#include <renderer/Vector.h>
#include <prims/Object.h>
#include <utils/Transforms.h>
#include <renderer/World.h>

using Eigen::Vector4d;
using namespace std;

Camera::Camera(Point pos, Vector look, Vector base, World w)
{
	objects = vector<Object>();
	screen = vector<vector<double>>();
	world = w;

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

	//Translation vector from world origin to camera position
	Vector dX = world.origin.subtract(eyepoint);

	//set view transform with v as X-axis, u/up as Y-axis, and n/lookat as Z-axis
	this->viewtransform = Transforms::viewTransform(v.vec, u.vec, n.vec, dX.vec);

}
