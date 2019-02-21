#include <renderer/World.h>

using namespace std;

World::World() : World(0,0,0)
{
}

World::World(double x, double y, double z)
{
	this->origin = Point(x, y, z);
	this->objects = vector<Object*>();
	this->nextId = 1;
}

int World::addObject(Object* obj)
{
	obj->id = this->nextId;
	this->nextId++;

	this->objects.push_back(obj);

	return obj->id;
}

bool World::removeObject(int objectId)
{
	//Very primitive, do a linear search for the object id
	//and remove if found.
	for (auto itr = objects.begin(); itr != objects.end(); itr++) {
		if ((*itr)->id == objectId) {
			objects.erase(itr);
			return true;
		}
	}

	//Object not found
	return false;
}

bool World::removeObject(Object* obj)
{
	return removeObject(obj->id);
}

void World::clear()
{
	for (int i = objects.size()-1; i >= 0; i--) {
		Object* cur = objects[i];
		delete cur;
		objects.pop_back();
	}
}
