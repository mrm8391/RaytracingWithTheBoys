/*
Model for a scene's world in the renderer.
*/

#ifndef RT_WORLD_H

#include <vector>

#include "../prims/Object.h"

class World {
	
public:
	World();
	std::vector<Object> objects;
};


#endif
