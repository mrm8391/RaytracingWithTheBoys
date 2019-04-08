
#include <vector>
#include <Eigen/Core>
#include <iostream>

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

double Camera::SCREEN_WIDTH = 3.0;
double Camera::SCREEN_HEIGHT = 3.0;

unsigned int Camera::NUM_PIXELS_HORIZONTAL = 400;
unsigned int Camera::NUM_PIXELS_VERTICAL = 400;

double Camera::PIXEL_WIDTH = Camera::SCREEN_WIDTH / Camera::NUM_PIXELS_HORIZONTAL;
double Camera::PIXEL_HEIGHT = Camera::SCREEN_HEIGHT / Camera::NUM_PIXELS_VERTICAL;

double Camera::FOCAL_POINT = 5.0;

Camera::Camera(Point pos, Vector look, Vector base)
{
	objects = vector<Object*>();
	lights = vector<LightSource*>();
	screen = vector<vector<Vector>>();

	eyepoint = Point(pos);
	lookat = Vector(look);
	lookat.normalize();

	//Configure camera coordinate system.
	//Positive z-axis in direction of lookat
	//Positive y-axis in direction of up, above camera and orthogonal to lookat
	//Positive x-axis to right of camera, orthogonal to lookat and up
	
	//For world space, we are treating +x to be right, +y to be up, and +z to be away from the viewer.
	//Thus, cross products are done in an unconventional order.
	n = Vector(lookat);
	v = base.cross(n);
	v.normalize();
	up = n.cross(v);
	up.normalize();
	u = Vector(up);
}

std::vector<std::vector<Vector>> Camera::render(World world)
{

	//Initialize virtual screen values. Default value/bg color is black
	vector<vector<Vector>> pixels;
	Vector backgroundColor = Vector(0.8, 0.8, 2.3);
	for (int i = 0; i < Camera::NUM_PIXELS_HORIZONTAL; i++) {
		pixels.push_back(vector<Vector>());

		for (int j = 0; j < Camera::NUM_PIXELS_VERTICAL; j++) {
			pixels[i].push_back(backgroundColor);
		}
	}


	//Nuke current object list, so it can be repopulated.
	this->clear();

	//Translation vector from world origin to camera position
	Vector dX = world.origin.subtract(eyepoint);

	//set view transform with v as X-axis, u/up as Y-axis, and n/lookat as Z-axis
	Matrix4d viewTransform = Transforms::viewTransform(v.vec, u.vec, n.vec, dX.vec);

	for (Object* obj : world.objects) {
		Object* cameraObj = obj->copy();
		cameraObj->transform(viewTransform);

		this->objects.push_back(cameraObj);
	}

	for (LightSource* light : world.lights) {
		LightSource* cameraLight = light->copy();
		cameraLight->transform(viewTransform);

		this->lights.push_back(cameraLight);
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

			IntersectData closestInter = spawnRay(pixelPos, rayDir);

			if (!closestInter.noIntersect) {
				// We have spawned a ray from the camera and hit an object in the scene!

				Vector color;

				// need to spawn ray from closestInter.intersection to each light source.
				for (LightSource * light : lights) {
					Vector lightSourceRayDir = light->pos.subtract(closestInter.intersection);
					//(double(light->pos.vec[0]), double(light->pos.vec[1]), double(light->pos.vec[2]));
					lightSourceRayDir.normalize();
					IntersectData potentialBlocker = spawnRay(closestInter.intersection, lightSourceRayDir);

					rayDir.normalize();
					Ray rayFromCamera(pixelPos, rayDir);

					// if it reaches the light source without intersection, then closestInter.intersectedObject->shade() gives the color
					if (potentialBlocker.noIntersect) {

						Ray ray(closestInter.intersection, lightSourceRayDir);

						color = closestInter.intersectedObject->shade(*light, rayFromCamera, closestInter);
						
						// change: reflect change in parameters: new params for all shading models.shade() will be: 
							// not LightSOurce anymore, but instead our own Vector containing redRad, greenRad, blueRad, and then a Position

					} 
					//if collision with an obj, shadow ray
					else {
						color = closestInter.intersectedObject->material->colorAtUV(0,0);
					}

				}
				pixels[x][y] = color;
				
			}
		}
	}

	//Set instance variables
	this->currentWorld = world;
	this->currentViewTransform = viewTransform;

	return pixels;
}

// Usage for this method is like this: 
// We found an intersection between an object and a camera ray. Grand. We need to know its illumination.
// Spawn a ray from the intersect point to the light source point
// Intersect checks with every object in scene 
// If there is an intersection with THIS lighting ray and an object, then that light source is blocked
// Otherwise, that light source shines on the point, return radiance onto that point. 

/*
This method tells you what object this ray first intersects with. 
If no intersection with an object is found, then its returned IntersectData instance will have noIntersect = TRUE. 
*/
IntersectData Camera::spawnRay(Point position, Vector rayDir) {
	rayDir.normalize();

	Ray ray(position, rayDir);

	IntersectData closestInter;

	for (Object* obj : this->objects) {

		IntersectData inter = obj->intersect(ray);
		if (!inter.noIntersect) { // if there is an intersection
			
			//prevent backwards inters, and intersection with itself if spawning ray from obj
			if (inter.distance < 0.001)
				continue;

			if (closestInter.noIntersect || inter.distance < closestInter.distance) { // if there was no intersection before, or this intersection is closer
				closestInter = inter;
			}
		}
	}

	return closestInter; 
}


void Camera::clear()
{
	for (int i = objects.size() - 1; i >= 0; i--) {
		Object* cur = objects[i];
		delete cur->shadingModel;
		delete cur;
		objects.pop_back();
	}

	for (int i = lights.size() - 1; i >= 0; i--) {
		LightSource* cur = lights[i];
		delete cur;
		lights.pop_back();
	}
}
