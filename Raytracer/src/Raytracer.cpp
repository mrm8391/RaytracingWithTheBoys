// Raytracer.cpp : Defines the entry point for the console application.
//

#include <iostream>

#include <fstream>
#include <string>

// 'C:\Users\tjwat_000\source\repos\RaytracingWithTheBoys\Raytracer\packages'
#include <boost/algorithm/string.hpp>

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


// Initializes all triangles
// You may have to write the full path to fileName
vector<Triangle *> loadHexagons(std::string fileName) {
	//unshaded material for object that don't refract
	SolidMaterial * invisibleMaterial = new SolidMaterial(Vector(0, 0, 0), 0, 0, 0, 0, Vector(0, 0, 0));

	// Layers
	vector<SolidMaterial *> layerMaterials;
	layerMaterials.push_back(new SolidMaterial(Vector(76.0/255.0, 97.0/255.0, 47.0/255.0), 0.8, 0.5, 0.3, 30.0, Vector(1.0, 1.0, 1.0))); // layer 0
	layerMaterials.push_back(new SolidMaterial(Vector(133.0 / 255.0, 158.0 / 255.0, 94.0 / 255.0), 0.8, 0.5, 0.3, 30.0, Vector(1.0, 1.0, 1.0))); // layer 1
	layerMaterials.push_back(new SolidMaterial(Vector(101.0 / 255.0, 85.0 / 255.0, 57.0 / 255.0), 0.8, 0.5, 0.3, 30.0, Vector(1.0, 1.0, 1.0))); // layer 2

	// This vector will contain every triangle
	vector<Triangle *> allTriangles;

	// For every line in the file, expecting format: (x, y, z); (x, y, z); (x, y, z); layer
	string line;
	ifstream hexagonFile(fileName);
	if (hexagonFile.is_open()) {
		while (getline(hexagonFile, line)) {
			// line contains three points in first three elements, and layer in last element, separated by ";"
			std::vector<std::string> pointsAndLayer;
			boost::split(pointsAndLayer, line, [](char c) {return c == ';'; });

			// Split each point into its double coordinates, and instantiate three Points
			std::vector<std::string> coordinates;

			boost::split(coordinates, pointsAndLayer[0], [](char c) {return c == ','; });
			Point p0(stod(coordinates[0]), stod(coordinates[1]), stod(coordinates[2]));

			boost::split(coordinates, pointsAndLayer[1], [](char c) {return c == ','; });
			Point p1(stod(coordinates[0]), stod(coordinates[1]), stod(coordinates[2]));

			boost::split(coordinates, pointsAndLayer[2], [](char c) {return c == ','; });
			Point p2(stod(coordinates[0]), stod(coordinates[1]), stod(coordinates[2]));

			// The layer of this triangle
			int layer = stoi(pointsAndLayer[3]);

			// Push back a new triangle into allTriangles, with those three Points and the Material corresponding to the layer
			Triangle* newTriangle = new Triangle(p0, p1, p2);
			newTriangle->setMaterials(layerMaterials[layer], invisibleMaterial);

			allTriangles.push_back(newTriangle);


		}
		hexagonFile.close();
	}
	else {
		cout << "Error: Could not open " << fileName << ".\n";
	}




	return allTriangles;
}


int main()
{
	vector<Triangle *> allTriangles = loadHexagons("C:\\Users\\tjwat_000\\source\\repos\\RaytracingWithTheBoys\\Raytracer\\src\\3DhexagonsShortened.txt");
	
	Point firstLightPoint(-1.8, 4.75, -6.0);
	// Low: 80
	// Mid: 145
	// High: 210
	LightSource* firstLight = new LightSource(firstLightPoint, 180, 180, 180); 

	World w;
	//w.addObject(floor1);
	//w.addObject(floor2);
	//w.addObject(largeSphere);
	//w.addObject(smallSphere);
	for (Triangle * triangle : allTriangles) {
		w.addObject(triangle);
	}

	w.addLightSource(firstLight);

	Point camOrig(-.8, 1.0, -11.14);
	Point worldOrig(0, 0, 0);
	Vector lookat(0, 0.1, 1);
	Vector base(0, 1, 0);

	Camera cam(camOrig, lookat, base);
	cout << "Rendering...\n";
	auto pixels = cam.render(w);
	
	//pixels = ToneReproduction::LinearScale(pixels);
	pixels = ToneReproduction::WardScale(pixels);

	Imager img(pixels);

	img.displayImage();
	img.saveImage("LogScalingHigh");

	//Deallocate object memory usage
	w.clear();
	cam.clear();

	// Supposed to delete materials

    return 0;
}

