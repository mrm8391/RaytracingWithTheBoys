// Raytracer.cpp : Defines the entry point for the console application.
//

#include <iostream>

#include <renderer/Camera.h>
#include <renderer/Point.h>
#include <renderer/Vector.h>
#include <renderer/World.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <utils/Transforms.h>

using namespace std;
using Eigen::MatrixXd;
using Eigen::Matrix;
using Eigen::StorageOptions;

//using namespace Eigen;
using Eigen::Vector3d;

/*
Test a camera looking at the origin.

Result should be a point that's 1 unit away on the z-axis
*/
void test_camera() {
	World world;

	//Origin in a spot that will have a hypotenuse of 1, each side sqrt(2)/2
	Point cam_origin(0, 0.7071, 0.7071);
	Vector look(0, -1, -1);
	Vector base(0, 0, -1);

	Camera cam(cam_origin, look, base, world);

	Eigen::Matrix4d viewtransform = cam.viewtransform;

	Eigen::Vector4d test;
	test << 0, 0, 0, 1;

	auto res = viewtransform * test;

	cout << "xform: \n" << viewtransform << endl << endl;
	cout << "point b4: \n" << test << endl << endl;
	cout << "xformed point: \n" << res << endl << endl;
}

int main()
{
	

    return 0;
}

