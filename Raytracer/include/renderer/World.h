/*
Model for a scene's world in the renderer.
*/

#ifndef RT_WORLD_H
#define RT_WORLD_H

#include <vector>

#include <prims/Object.h>
#include <renderer/Point.h>

class World {
	
public:
	std::vector<Object> objects;
	Point origin;
	
	/*
	Default constructor, creating a world with origin (0,0,0)
	*/
	World();

	/*
	Create a world with an alternative origin if feeling masochistic
	*/
	World(double x, double y, double z);
};


#endif
