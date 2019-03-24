
#include <renderer/lighting/LightSource.h>

LightSource::LightSource()
{
}

LightSource::LightSource(Point position, double redRad, double greenRad, double blueRad) : pos(position), radiance(redRad, greenRad, blueRad)
{
}

LightSource* LightSource::copy()
{
	LightSource* l = new LightSource(*this);

	l->radiance = this->radiance;
	l->pos = this->pos;
	l->id = this->id;

	return l;
}

void LightSource::transform(Eigen::Matrix4d matr)
{
	pos.transform(matr);
}
