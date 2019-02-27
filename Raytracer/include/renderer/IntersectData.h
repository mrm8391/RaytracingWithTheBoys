/*
Small bundle of information for conveying information regarding
a ray-object intersection.
*/

#ifndef RT_INTERSECT_H
#define RT_INTERSECT_H

#include <renderer/Point.h>

class Object;

typedef struct IntersectData_{

	//How far along the ray the intersection occurs
	double distance;

	//Color of the material hit by the ray TODO potentially remove this
	double color;

	// Normal vector of the object at the point of intersection
	Vector normal;

	// The object at the point of intersection
	Object * closestObject;

	//Point at which the intersection occurs (optional)
	Point intersection;

	//If true, no intersection occurs
	bool noIntersect;

	// A pointer to the object which was found to be intersected

	/*
	Default constructor to indicate no intersection
	*/
	IntersectData_() : noIntersect(true)
	{
	}

	IntersectData_(double d, double c, Vector n, Object * obj, Point i) : distance(d), color(c), normal(n), closestObject(obj), intersection(i), noIntersect(false) 
	{
	}

} IntersectData;

#endif