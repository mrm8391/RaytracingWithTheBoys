#include <renderer/World.h>

using namespace std;

World::World() : World(0,0,0)
{
}

World::World(double x, double y, double z)
{
	this->origin = Point(x, y, z);
	this->objects = vector<Object>();
}

unsigned int World::addObject(Object obj)
{
	this->objects.push_back(obj);

	return obj.id;
}

bool World::removeObject(int objectId)
{
	//Very primitive, do a linear search for the object id
	//and remove if found.
	for (auto itr = objects.begin(); itr != objects.end(); itr++) {
		if (itr->id == objectId) {
			objects.erase(itr);
			return true;
		}
	}

	//Object not found
	return false;
}

bool World::removeObject(Object obj)
{
	return removeObject(obj.id);
}
