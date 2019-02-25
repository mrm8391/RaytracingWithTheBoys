/*
Abstract base class for primitive objects that can be placed in the scene.

These will be mathematically defined.
*/

#ifndef RT_OBJECT_H
#define RT_OBJECT_H

#include <vector>

#include <renderer/Point.h>
#include <renderer/Ray.h>
#include <renderer/IntersectData.h>
#include <renderer/lighting/LightSource.h>
#include <renderer/lighting/ShadingModel.h>
#include <renderer/lighting/PhongShading.h>

class Object {

public:

	Point pos;

	// For now, a 0-1 value
	double color;

	// Object's id, for use by the world/camera
	int id;

	// Illumination model for determining lighting/reflection on surface
	ShadingModel shadingModel;

	/*
	Default constructor, placing object at (0,0,0)

	Only intended to be used by derivative classes, object shouldn't
	be constructed alone.
	*/
	Object();

	/*
	Construct an object at a specified position, and assign it a unique ID.
	*/
	Object(double x, double y, double z, ShadingModel shad = PhongShading());

	/*
	Performs an intersection test on the object with a ray, finding the closest intersection point.
	IntersectData struct is returned containing info on intersection point and color of object.
	IntersectData.noIntersect is true if there is no intersection between the ray and the object.

	The ray must be normalized, otherwise there will be undefined behavior.
	*/
	virtual IntersectData intersect(Ray ray);

	/*
	At a given point of intersection, compute the radiance collected on that point for the object.

	By this point, camera has spawned rays to determine which lights have rays hitting the object.
	This method only gets called for light sources successfully reaching this intersection.

	An illumination model is applied to the incoming radiance, computing the output radiance from
	the intersection point.

	@param light - Light source hitting the point
	@param incoming - Incoming ray that is intersecting with object
	@param inter - Intersection point on the object.

	@return Resulting radiance after applying an illumination model on the point
	*/
	virtual Vector shade(LightSource light, Ray incoming, IntersectData inter);

	virtual void translate(double x, double y, double z);

	virtual void move(double x, double y, double z);

	/*
	Transform object by an arbitrary transformation matrix, typically a view transform.
	Modifies current object.

	For now, this will only make sense for 2D objects (like triangles) or objects that are rotationally symmetric (like spheres).
	Will have to find a solution for other cases later.

	@param matr Transformation matrix to apply to the object
	*/
	virtual void transform(Eigen::Matrix4d matr);

	virtual Object* copy();
};

#endif