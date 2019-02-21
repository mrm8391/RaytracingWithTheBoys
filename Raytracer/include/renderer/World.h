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
	std::vector<Object*> objects;
	Point origin;
	int nextId;
	
	/*
	Default constructor, creating a world with origin (0,0,0)
	*/
	World();

	/*
	Create a world with an alternative origin if feeling masochistic
	*/
	World(double x, double y, double z);

	/*
	Add an object to the world and assign it an ID. 
	Object assumed to be initialized and ready for display.

	@param obj Object to add
	
	@return Id of inserted object
	*/
	int addObject(Object* obj);

	/*
	Remove an object from the world based on its id.

	@param objectId Id of the object

	@return True if removal successful, false otherwise. May replace this with an exception later
	*/
	bool removeObject(int objectId);

	/*
	Remove an object from the world. Helper function, merely grabs the id and calls the
	overloaded version of this method.

	@param obj The object to remove

	@return True if removal successful, false otherwise.
	*/
	bool removeObject(Object* obj);

	/*
	Clear all objects in world and deallocate from the heap.
	*/
	void clear();
};


#endif
