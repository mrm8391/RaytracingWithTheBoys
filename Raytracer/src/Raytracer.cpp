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
#include <prims/Sphere.h>

using namespace std;
using Eigen::MatrixXd;
using Eigen::Matrix;
using Eigen::StorageOptions;

//using namespace Eigen;
using Eigen::Vector3d;

int main()
{
	World w;

	Point f1(-10, 0, 0), f2(-10, 0, 10), f3(10, 0, 0), f4(10, 0, 10);
	Triangle floor1(f1, f2, f3), floor2(f2, f3, f4);

	Point s1(0, 0, 0);
	Sphere sphere1(s1, 2.0);
	sphere1.color = 0.5;

	w.addObject(floor1);
	w.addObject(floor2);
	w.addObject(sphere1);

	Point camOrig(0, 2, 10);
	Vector lookat(0, 0, 0), base(0, 1, 0);

	Camera cam(camOrig, lookat, base);

	auto pixels = cam.render(w);

	for (int x = 0; x < pixels.size(); x++) {
		for (int y = 0; y < pixels[x].size(); y++) {

			int val = int(pixels[x][y] * 100);
			cout << val << " ";
		}

		cout << endl;
	}

    return 0;
}

