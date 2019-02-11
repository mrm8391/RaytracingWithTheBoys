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

class Object {

public:
	static unsigned int NEXT_ID;

	Point pos;

	// For now, a 0-1 value
	double color;
	unsigned int id;

	/*
	Default constructor, placing object at origin and assigning a unique ID.

	Only intended to be used by derivative classes, object shouldn't
	be constructed alone.
	*/
	Object();

	/*
	Construct an object at a specified position, and assign it a unique ID.
	*/
	Object(double x, double y, double z);

	/*
	Copy constructor; create new object from an old one. Does not assign a new ID,
	copies ID from old object.

	@param other Object to copy
	*/
	Object(const Object &other);

	// Returns array of intersections with that object
	virtual IntersectData* intersect(Ray ray);

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

	/*
	Copy object, and transform it with a transformation matrix. Intended for use when
	transforming world objects into camera space. New object will not have a unique ID, will
	have the ID of this object.

	@param matr Transformation matrix to apply to the object

	@return New, transformed version of current object. Transformed object will have the same ID.
	*/
	virtual Object* transformAndCopy(Eigen::Matrix4d matr);
};

#endif