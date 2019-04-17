
#include <vector>
#include <Eigen/Core>
#include <iostream>

#include <renderer/Camera.h>
#include <renderer/Point.h>
#include <renderer/Vector.h>
#include <prims/Object.h>
#include <utils/Transforms.h>
#include <renderer/World.h>
#include <renderer/materials/Material.h>

using Eigen::Vector4d;
using Eigen::Matrix4d;
using namespace std;

//Static runtime constant initialization

double Camera::SCREEN_WIDTH = 3.0;
double Camera::SCREEN_HEIGHT = 3.0;

unsigned int Camera::NUM_PIXELS_HORIZONTAL = 200;
unsigned int Camera::NUM_PIXELS_VERTICAL = 200;

double Camera::PIXEL_WIDTH = Camera::SCREEN_WIDTH / Camera::NUM_PIXELS_HORIZONTAL;
double Camera::PIXEL_HEIGHT = Camera::SCREEN_HEIGHT / Camera::NUM_PIXELS_VERTICAL;

double Camera::FOCAL_POINT = 5.0;

int Camera::MAX_ILLUMINATE_DEPTH = 3;

Vector Camera::BACKGROUND_COLOR = Vector(0.61 * 4, 1.48 * 4, 2.3 * 4);

double Camera::ATMOSPHERE_INDEX_OF_REFRACTION = 1.0;

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

	//Initialize virtual screen values. Default value/bg color is blue
	vector<vector<Vector>> pixels;
	for (int i = 0; i < Camera::NUM_PIXELS_HORIZONTAL; i++) {
		pixels.push_back(vector<Vector>());

		for (int j = 0; j < Camera::NUM_PIXELS_VERTICAL; j++) {
			pixels[i].push_back(BACKGROUND_COLOR);
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
			rayDir.normalize();

			Ray cameraRay(pixelPos, rayDir);

			IntersectData closestInter = spawnRay(cameraRay);
			
			Vector color = illuminate(closestInter, 0);
			pixels[x][y] = color;
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
IntersectData Camera::spawnRay(Ray spawnedRay) {

	IntersectData closestInter;

	for (Object* obj : this->objects) {

		vector<IntersectData> inters = obj->intersect(spawnedRay);
		if (!inters.empty()) { // if there is an intersection
			
			//Find the closest intersection on this object that isn't the same point where the ray originated.
			//Hack to get objects to cast shadows on themselves.
			IntersectData closestOnObj;
			for (IntersectData& in : inters) {

				//Ignore intersections behind spawned ray as well as points near ray spawn point
				if (in.distance < 0.0001)
					continue;

				else if (closestOnObj.noIntersect || in.distance < closestOnObj.distance) {
					closestOnObj = in;
				}
			}

			if (closestInter.noIntersect || closestOnObj.distance < closestInter.distance) { // if there was no intersection before, or this intersection is closer
				closestInter = closestOnObj;
			}
		}
	}

	closestInter.ray = spawnedRay;

	//invert normal if ray is refracting and intersecting inside of object
	if (closestInter.intersectedObject == spawnedRay.spawnedInside) {
		closestInter.normal = closestInter.normal.scale(-1);
	}

	return closestInter; 
}

Vector Camera::illuminate(IntersectData intersection, int depth)
{
	Vector color;

	// We have hit another object.  
	if (!intersection.noIntersect) {

		//Material to apply. Use inner material if intersection
		//is occurring from a ray that was spawned inside object
		Material* applicableMaterial;

		//Indices of refraction to use. n1 is index from source of ray, n2 is from destination
		double n1, n2;

		//Since no recursive object placement is planned, we're going to assume
		//that the ray origin is spawned inside the current intersected object
		//if there's a non-null object for the ray
		if (intersection.ray.spawnedInside != 0) {
			applicableMaterial = intersection.intersectedObject->innerMaterial;
			n1 = intersection.intersectedObject->innerMaterial->n;
			n2 = Camera::ATMOSPHERE_INDEX_OF_REFRACTION;
		}

		//Object must be intersected from outside then
		else {
			applicableMaterial = intersection.intersectedObject->outerMaterial;
			n1 = Camera::ATMOSPHERE_INDEX_OF_REFRACTION;
			n2 = intersection.intersectedObject->outerMaterial->n;
		}
		
		double kr = applicableMaterial->kr;
		double kt = applicableMaterial->kt;

		// Calculates color at that point due to shadow rays 
		color = locallyShade(intersection);

		if (depth < MAX_ILLUMINATE_DEPTH) {
			// If reflection constant is nonzero, recursively calculate reflection 
			if (kr > 0.0) {
				// Spawn ray in reflected direction
				Vector reflectedDirection = intersection.ray.direction.reflect(intersection.normal);
				reflectedDirection.normalize();

				Ray reflectedRay(intersection.intersection, reflectedDirection);

				//Since it's reflection, object medium will be same as original source ray's
				reflectedRay.spawnedInside = intersection.ray.spawnedInside;

				IntersectData nextReflection = spawnRay(reflectedRay);
				Vector reflColor = illuminate(nextReflection, depth + 1);

				color.vec += reflColor.scale(kr).vec;
			}

			// If transmission constant is nonzero, recursively calculate transmission 
			if (kt > 0.0) {
				// Spawn ray in refracted direction. spawnRay from previous recursive call should 
				// be handling the inverted normal if ray is intersecting from inside.

				Vector transmittedDirection = intersection.ray.direction.refract(intersection.normal, n1, n2);
				transmittedDirection.normalize();

				Ray refractedRay(intersection.intersection, transmittedDirection);

				//If coming from outside, refracted ray will be going through intersected object
				if (intersection.ray.spawnedInside == 0)
					refractedRay.spawnedInside = intersection.intersectedObject;

				IntersectData nextTransmission = spawnRay(refractedRay);
				Vector transmColor = illuminate(nextTransmission, depth + 1);

				color.vec += transmColor.scale(kt).vec;
			}
		}
	}
	else {
		// We have not hit another object. The light coming back along this ray is the background color. 
		color = BACKGROUND_COLOR;
	}

	return color;
}

Vector Camera::locallyShade(IntersectData closestInter) {
	Vector color;

	// need to spawn ray from closestInter.intersection to each light source.
	for (LightSource * light : lights) {
		Vector lightSourceRayDir = light->pos.subtract(closestInter.intersection);
		lightSourceRayDir.normalize();

		Ray shadowRay(closestInter.intersection, lightSourceRayDir);

		//medium of shadow ray is wherever the original ray was spawned
		shadowRay.spawnedInside = closestInter.ray.spawnedInside;

		IntersectData potentialBlocker = spawnRay(shadowRay);

		// if it reaches the light source without intersection, OR the intersected object is transmissive,
		// then closestInter.intersectedObject->shade() gives the color
		if ((potentialBlocker.noIntersect) || (potentialBlocker.intersectedObject->outerMaterial->kt != 0)) {
			Ray ray(closestInter.intersection, lightSourceRayDir);
			color = closestInter.intersectedObject->shade(*light, closestInter.ray, closestInter);

			// change: reflect change in parameters: new params for all shading models.shade() will be: 
			// not LightSOurce anymore, but instead our own Vector containing redRad, greenRad, blueRad, and then a Position
		}
		//if collision with an obj, shadow ray
		else {
			color = closestInter.intersectedObject->outerMaterial->colorAtUV(closestInter.u, closestInter.v);
		}
	}

	return color;
}


void Camera::clear()
{
	for (int i = objects.size() - 1; i >= 0; i--) {
		Object* cur = objects[i];
		delete cur->shadingModel;

		//placeholder. should copy/free material in here...
		if (cur->outerMaterial != 0) {
			//delete cur->outerMaterial;
			//cur->outerMaterial = 0;
		}

		delete cur;
		objects.pop_back();
	}

	for (int i = lights.size() - 1; i >= 0; i--) {
		LightSource* cur = lights[i];
		delete cur;
		lights.pop_back();
	}
}
