
#include <vector>
#include <Eigen/Core>

#include <renderer/Camera.h>
#include <renderer/Point.h>
#include <renderer/Vector.h>
#include <prims/Object.h>
#include <utils/Transforms.h>
#include <renderer/World.h>

using Eigen::Vector4d;
using Eigen::Matrix4d;
using namespace std;

//Static runtime constant initialization

double Camera::SCREEN_WIDTH = 10.0;
double Camera::SCREEN_HEIGHT = 10.0;

unsigned int Camera::NUM_PIXELS_HORIZONTAL = 10;
unsigned int Camera::NUM_PIXELS_VERTICAL = 10;

double Camera::PIXEL_WIDTH = Camera::SCREEN_WIDTH / Camera::NUM_PIXELS_HORIZONTAL;
double Camera::PIXEL_HEIGHT = Camera::SCREEN_HEIGHT / Camera::NUM_PIXELS_VERTICAL;

double Camera::FOCAL_POINT = 5.0;

Camera::Camera(Point pos, Vector look, Vector base)
{
	objects = vector<Object>();
	screen = vector<vector<double>>();

	eyepoint = Point(pos);
	lookat = Vector(look);
	lookat.normalize();

	//Configure camera coordinate system.
	//Positive z-axis in direction of lookat
	//Positive y-axis in direction of up, above camera and orthogonal to lookat
	//Positive x-axis to right of camera, orthogonal to lookat and up

	n = Vector(lookat);
	v = n.cross(base);
	v.normalize();
	up = v.cross(n);
	up.normalize();
	u = Vector(up);
}

std::vector<std::vector<double>> Camera::render(World world)
{

	//Initialize virtual screen values. Default value/bg color is
	//maximum intensity, white.
	vector<vector<double>> pixels;
	for (int i = 0; i < Camera::NUM_PIXELS_HORIZONTAL; i++) {
		pixels.push_back(vector<double>());

		for (int j = 0; j < Camera::NUM_PIXELS_VERTICAL; j++) {
			pixels[i].push_back(1.0);
		}
	}


	//Nuke current object list, so it can be repopulated.
	//Do proper memory management if we use the heap later
	this->objects = vector<Object>();

	//Translation vector from world origin to camera position
	Vector dX = world.origin.subtract(eyepoint);

	//set view transform with v as X-axis, u/up as Y-axis, and n/lookat as Z-axis
	Matrix4d viewTransform = Transforms::viewTransform(v.vec, u.vec, n.vec, dX.vec);

	for (Object &obj : world.objects) {
		Object cameraObj = obj.transformAndCopy(viewTransform);

		this->objects.push_back(cameraObj);
	}

	//Start spawning rays.
	//In accordance with the camera coordinate system,
	//+x goes to the right of screen, +y to the top of screen,
	//and all pixels on the screen are at z=focal point

	//Start point of ray tracer, beginning at bottom left.
	Point startPoint(
		(-0.5)*Camera::SCREEN_WIDTH,
		(-0.5)*Camera::SCREEN_HEIGHT,
		Camera::FOCAL_POINT
	);

	//Offset to get to center of pixel
	double pixelYOffset = (0.5)*Camera::PIXEL_HEIGHT,
		pixelXOffset = (0.5)*Camera::PIXEL_WIDTH;

	Point cameraOrigin(0, 0, 0);

	for (int x = 0; x < Camera::NUM_PIXELS_HORIZONTAL; x++) {

		for (int y = 0; y < Camera::NUM_PIXELS_VERTICAL; y++) {

			//Center of current pixel of virtual scren
			Point pixelPos(
				startPoint.vec[0] + (Camera::PIXEL_WIDTH * x) + pixelXOffset,
				startPoint.vec[1] + (Camera::PIXEL_HEIGHT * y) + pixelYOffset,
				Camera::FOCAL_POINT
			);

			Vector rayDir = pixelPos.subtract(cameraOrigin);
			rayDir.normalize();

			Ray rayToPixel(pixelPos, rayDir);

			IntersectData closestInter;
			Object closestObj;

			for (Object &obj : this->objects) {
				
				IntersectData inter = obj.intersect(rayToPixel);
				if (!inter.noIntersect) {
					if (closestInter.noIntersect || inter.distance < closestInter.distance) {
						closestInter = inter;
						closestObj = obj;
					}
				}

			if (!closestInter.noIntersect) {
				pixels[x][y] = closestInter.color;
			}
		}
	}

	//Set instance variables
	this->currentWorld = world;
	this->currentViewTransform = viewTransform;

	return pixels;
}
