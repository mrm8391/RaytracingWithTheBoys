// Raytracer.cpp : Defines the entry point for the console application.
//

#include <iostream>

#include <renderer/Camera.h>
#include <renderer/Point.h>
#include <renderer/Vector.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace std;
using Eigen::MatrixXd;
using Eigen::Matrix;
using Eigen::StorageOptions;

using namespace Eigen;
using Eigen::Vector3d;

int main()
{
	Point origin(0, 0, 0);
	Vector look(1, 0, 0);
	Vector up(0, 1, 0);

	Camera cam(origin, look, up);



    return 0;
}

