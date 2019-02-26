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

	Point f1(-2, 0, -6), f2(-2, 0, 6), f3(2, 0, 6), f4(2, 0, -6);
	Triangle* floor1 = new Triangle(f1, f2, f4);
	Triangle* floor2 = new Triangle(f4, f2, f3);
	floor1->color = .75;
	floor2->color = .75;

	Point largeSpherePoint(-1.0, 1.3, -1.9);
	Sphere* largeSphere = new Sphere(largeSpherePoint, 1.0);
	largeSphere->color = 0.25;

	Point smallSpherePoint(0.0, .7, -1.2);
	Sphere* smallSphere = new Sphere(smallSpherePoint, 0.75);
	smallSphere->color = 0.5;

	World w;
	w.addObject(floor1);
	w.addObject(floor2);
	w.addObject(largeSphere);
	w.addObject(smallSphere);

	Point camOrig(-.8, .7, -6.14);
	Point worldOrig(0, 0, 0);
	Vector lookat(0, 0, 1);
	Vector base(0, 1, 0);

	Camera cam(camOrig, lookat, base);

	auto pixels = cam.render(w);

	Imager img(pixels);

	img.displayImage();

	//Deallocate object memory usage
	w.clear();
	cam.clear();

	//Object * h = 0;// obj(1, 2, 3);

    return 0;
}

