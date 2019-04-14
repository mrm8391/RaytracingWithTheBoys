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
#include <renderer/materials/SolidMaterial.h>
#include <renderer/Imager.h>
#include <renderer/lighting/ToneReproduction.h>
#include <renderer/materials/CheckerMaterial.h>

using namespace std;
using Eigen::MatrixXd;
using Eigen::Matrix;
using Eigen::StorageOptions;

//using namespace Eigen;
using Eigen::Vector3d;


int main()
{
	
	CheckerMaterial * floorMaterial = new CheckerMaterial(17, Vector(1.0, 1.0, 1.0), Vector(0.0, 0.0, 0.0));
	Point f1(-2, 0, -6), f2(-2, 0, 6), f3(2, 0, 6), f4(2, 0, -6);
	Triangle* floor1 = new Triangle(f1, f2, f4);
	Triangle* floor2 = new Triangle(f3, f4, f2);
	floor1->material = floorMaterial;
	floor2->material = floorMaterial;

	SolidMaterial * largeSphereMaterial = new SolidMaterial(Vector(1.0, 0.2, 0.0), 0.8, 0.5, 0.3, 30.0, Vector(1.0, 1.0, 1.0));
	Point largeSpherePoint(-1.0, 1.3, -1.9);
	Sphere* largeSphere = new Sphere(largeSpherePoint, 1.0);
	largeSphere->material = largeSphereMaterial;

	SolidMaterial * smallSphereMaterial = new SolidMaterial(Vector(0.0, 0.0, 1.0), 0.8, 0.5, 0.3, 30.0, Vector(1.0, 1.0, 1.0));
	Point smallSpherePoint(0.0, .7, -1.2);
	Sphere* smallSphere = new Sphere(smallSpherePoint, 0.75);
	smallSphere->material = smallSphereMaterial;
	
	Point firstLightPoint(-1.0, 5.3, -1.9);
	LightSource* firstLight = new LightSource(firstLightPoint, 10, 10, 10);

	World w;
	w.addObject(floor1);
	w.addObject(floor2);
	w.addObject(largeSphere);
	w.addObject(smallSphere);
	w.addLightSource(firstLight);


	Point camOrig(-.8, .7, -12.14);
	Point worldOrig(0, 0, 0);
	Vector lookat(0, 0, 1);
	Vector base(0, 1, 0);

	Camera cam(camOrig, lookat, base);

	auto pixels = cam.render(w);
	
	pixels = ToneReproduction::LinearScale(pixels);

	Imager img(pixels);

	img.displayImage();
	img.saveImage("checkpoint3");

	//Deallocate object memory usage
	w.clear();
	cam.clear();

	delete floorMaterial;
	delete smallSphereMaterial;
	delete largeSphereMaterial;

    return 0;
}

