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
#include <renderer/Imager.h>

using namespace std;
using Eigen::MatrixXd;
using Eigen::Matrix;
using Eigen::StorageOptions;

//using namespace Eigen;
using Eigen::Vector3d;


int main()
{
	Eigen::Vector4d test;
	test << 0, 0, 0, 1;

	Point f1(0, 0, 0), f2(0, 0, 50), f3(50, 0, 0), f4(50, 50, 0);
	Triangle* floor1 = new Triangle(f1, f2, f3);
	Triangle* floor2 = new Triangle(f4, f2, f1);
	floor1->color = .75;
	floor2->color = .75;

	/*Point s1(0, 0, 0);
	Sphere sphere1(s1, 2.0);
	sphere1.color = 0.5;*/

	World w;
	w.addObject(floor1);
	//w.addObject(floor2);
	//w.addObject(sphere1);

	Point camOrig(0, 0, -10);
	Point worldOrig(0, 0, 0);
	Vector lookat = worldOrig.subtract(camOrig);
	Vector base(0, 1, 0);

	Camera cam(camOrig, lookat, base);

	auto pixels = cam.render(w);

	Imager img(pixels);

	img.displayImage();


    return 0;
}

