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
	//unshaded material for object that don't refract
	SolidMaterial * invisibleMaterial = new SolidMaterial(Vector(0, 0, 0), 0, 0, 0, 0, Vector(0, 0, 0));
	
	CheckerMaterial * floorMaterial = new CheckerMaterial(17, Vector(1.0, 0.93, 0.46), Vector(0.9, 0.21, 0.3));
	floorMaterial->setReflective(0.0, 0.0);
	Point f1(-2, 0, -6), f2(-2, 0, 6), f3(2, 0, 6), f4(2, 0, -6);
	Triangle* floor1 = new Triangle(f1, f2, f4);
	Triangle* floor2 = new Triangle(f3, f4, f2);
	floor1->setMaterials(floorMaterial, invisibleMaterial);
	floor2->setMaterials(floorMaterial, invisibleMaterial);
	
	SolidMaterial * largeSphereMaterial = new SolidMaterial(Vector(0.01, 0.01, 0.01), 0.8, 0.5, 0.3, 30.0, Vector(1.0, 1.0, 1.0));
	SolidMaterial * innerGlassMaterial = new SolidMaterial(Vector(0.0,0.0, 0.0), 0.0, 0.0, 0.0, 0.0, Vector(0.0, 0.0, 0.0));
	largeSphereMaterial->setReflective(0.0, 1.0);
	innerGlassMaterial->setReflective(0.0, 1.0);
	largeSphereMaterial->n = 1.33;
	innerGlassMaterial->n = 1.33;
	Point largeSpherePoint(-1.0, 1.4, -1.9);
	Sphere* largeSphere = new Sphere(largeSpherePoint, 1.0);
	largeSphere->setMaterials(largeSphereMaterial, innerGlassMaterial);

	SolidMaterial * smallSphereMaterial = new SolidMaterial(Vector(0.0, 0.0, 1.0), 0.8, 0.5, 0.3, 30.0, Vector(1.0, 1.0, 1.0));
	smallSphereMaterial->setReflective(0.5, 0.0);
	Point smallSpherePoint(0.0, .8, 2.2);
	Sphere* smallSphere = new Sphere(smallSpherePoint, 0.75);
	smallSphere->setMaterials(smallSphereMaterial, invisibleMaterial);
	
	Point firstLightPoint(-1.8, 4.75, -6.0);
	// Low: 80
	// Mid: 145
	// High: 210
	LightSource* firstLight = new LightSource(firstLightPoint, 210, 210, 210); 

	World w;
	w.addObject(floor1);
	w.addObject(floor2);
	w.addObject(largeSphere);
	w.addObject(smallSphere);
	w.addLightSource(firstLight);

	Point camOrig(-.8, 1.0, -11.14);
	Point worldOrig(0, 0, 0);
	Vector lookat(0, 0.1, 1);
	Vector base(0, 1, 0);

	Camera cam(camOrig, lookat, base);

	auto pixels = cam.render(w);
	
	//pixels = ToneReproduction::LinearScale(pixels);
	pixels = ToneReproduction::AdaptiveLogarithmScale(pixels);

	Imager img(pixels);

	img.displayImage();
	img.saveImage("LogScalingHigh");

	//Deallocate object memory usage
	w.clear();
	cam.clear();

	delete invisibleMaterial;
	delete floorMaterial;
	delete smallSphereMaterial;
	delete largeSphereMaterial;
	delete innerGlassMaterial;

    return 0;
}

