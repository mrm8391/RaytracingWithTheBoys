#include <renderer/World.h>

using namespace std;

World::World() : World(0,0,0)
{
}

World::World(double x, double y, double z)
{
	this->origin = Point(x, y, z);
	this->objects = vector<Object*>();
	this->lights = vector<LightSource*>();
	this->nextId = 1; // ID for Objects
	this->nextLightId = 1; // ID for LightSources
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

int World::addLightSource(LightSource* lyte)
{
	lyte->id = this->nextLightId;
	this->nextLightId++;

	this->lights.push_back(lyte);

	return lyte->id;
}

void World::clear()
{
	for (int i = objects.size()-1; i >= 0; i--) {
		Object* cur = objects[i];

		//placeholder. should free shadingmodel + materials in world
		//delete cur->shadingModel;

		delete cur;
		objects.pop_back();
	}

	for (int i = lights.size() - 1; i >= 0; i--) {
		LightSource* cur = lights[i];
		delete cur;
		lights.pop_back();
	}
}
