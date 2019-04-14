/*
Small bundle of information for conveying information regarding
a ray-object intersection.
*/

#ifndef RT_INTERSECT_H
#define RT_INTERSECT_H

#include <renderer/Point.h>
#include <renderer/Ray.h>

class Object;

typedef struct IntersectData_{

	//How far along the ray the intersection occurs
	double distance;

	// Normal vector of the object at the point of intersection
	Vector normal;

	// The object at the point of intersection
	Object * intersectedObject;

	//Point at which the intersection occurs (optional)
	Point intersection;

	//UV mapping on object of this intersection for texturing. 
	//Should be bounded [0,1] and should be computed when intersection is computed
	float u, v;

	//If true, no intersection occurs
	bool noIntersect;

	// The ray which intersected the object
	Ray ray;

	/*
	Default constructor to indicate no intersection
	*/
	IntersectData_() : noIntersect(true)
	{
	}

	IntersectData_(double d, Vector n, Object * obj, Point i) : distance(d), normal(n), intersectedObject(obj), intersection(i), noIntersect(false), u(0), v(0)
	{
	}

	IntersectData_(const IntersectData_& other)
	{
		this->distance = other.distance;
		this->normal = other.normal;
		this->intersectedObject = other.intersectedObject;
		this->intersection = other.intersection;
		this->u = other.u;
		this->v = other.v;
		this->noIntersect = other.noIntersect;
		this->ray = other.ray;

	}

} IntersectData;

#endif