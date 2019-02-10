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
#include <prims/Triangle.h>

using namespace std;
using Eigen::MatrixXd;
using Eigen::Matrix;
using Eigen::StorageOptions;

//using namespace Eigen;
using Eigen::Vector3d;

int main()
{
	World w;

	Point p1(0, 0, 0), p2(1, 1, 1), p3(1, 1, 4), p4(1, 1, -4);

	Triangle t1(p1, p2, p3), t2(p1, p2, p4);

	int t1Id = w.addObject(t1);
	int t2Id = w.addObject(t2);

	cout << "succ" << endl;

	w.removeObject(t1Id);
	w.removeObject(t2);

    return 0;
}

