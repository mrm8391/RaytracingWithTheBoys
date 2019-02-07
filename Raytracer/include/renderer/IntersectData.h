/*
Small bundle of information for conveying information regarding
a ray-object intersection.
*/

#ifndef RT_INTERSECT_H
#define RT_INTERSECT_H

#include <renderer/Point.h>

typedef struct IntersectData_{

	//How far along the ray the intersection occurs
	double distance;

	//Color of the material hit by the ray
	double color;

	//Point at which the intersection occurs (optional)
	Point intersection;
} IntersectData;

#endif