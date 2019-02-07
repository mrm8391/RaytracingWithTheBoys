
#include <vector>
#include <Eigen/Core>

#include <renderer/Camera.h>
#include <renderer/Point.h>
#include <renderer/Vector.h>
#include <prims/Object.h>

using Eigen::Vector4d;
using namespace std;

Camera::Camera(Point pos, Vector look, Vector base)
{
	objects = vector<Object>();
	screen = vector<vector<double>>();

	eyepoint = Point(pos);
	lookat = Vector(look);
	lookat.normalize();

	n = Vector(lookat);
	
	v = n.cross(base);
	v.normalize();

	up = v.cross(n);
	up.normalize();

	u = Vector(up);


}
