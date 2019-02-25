
#include <renderer/lighting/LightSource.h>

LightSource::LightSource()
{
}

LightSource::LightSource(Point position, double redRad, double greenRad, double blueRad) : pos(position), radiance(redRad, greenRad, blueRad)
{
}
