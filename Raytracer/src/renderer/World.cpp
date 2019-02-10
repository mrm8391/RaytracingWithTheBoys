#include <renderer/World.h>

World::World() : World(0,0,0)
{
}

World::World(double x, double y, double z)
{
	this->origin = Point(x, y, z);
}
