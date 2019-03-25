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
#include <renderer/lighting/ToneReproduction.h>

using namespace std;
using Eigen::MatrixXd;
using Eigen::Matrix;
using Eigen::StorageOptions;

//using namespace Eigen;
using Eigen::Vector3d;


int main()
{
	Point f1(-2, 0, -6), f2(-2, 0, 6), f3(2, 0, 6), f4(2, 0, -6);
	Triangle* floor1 = new Triangle(f1, f2, f4);
	Triangle* floor2 = new Triangle(f4, f2, f3);
	floor1->color = Vector(0.0,1.0,0.0);
	floor2->color = Vector(0.0,1.0, 0.0);

	Point largeSpherePoint(-1.0, 1.3, -1.9);
	Sphere* largeSphere = new Sphere(largeSpherePoint, 1.0);
	largeSphere->color = Vector(1.0,0.2,0.0);

	Point smallSpherePoint(0.0, .7, -1.2);
	Sphere* smallSphere = new Sphere(smallSpherePoint, 0.75);
	smallSphere->color = Vector(0.0,0.0,1.0);

	Point firstLightPoint(-1.2, 3.00, 5.11);
	LightSource* firstLight = new LightSource(firstLightPoint, 10, 10, 10);

	World w;
	w.addObject(floor1);
	w.addObject(floor2);
	w.addObject(largeSphere);
	w.addObject(smallSphere);
	w.addLightSource(firstLight);


	Point camOrig(-.8, .7, -6.14);
	Point worldOrig(0, 0, 0);
	Vector lookat(0, 0, 1);
	Vector base(0, 1, 0);

	Camera cam(camOrig, lookat, base);

	auto pixels = cam.render(w);

	// pixels is a 2d vector of Vectors of unbounded R,G,B radiances at this point
	
	pixels = ToneReproduction::LinearScale(pixels);

	Imager img(pixels);

	img.displayImage();
	img.saveImage("coloredPhongTest");

	//Deallocate object memory usage
	w.clear();
	cam.clear();

    return 0;
}

