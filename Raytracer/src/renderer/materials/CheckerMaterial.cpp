
#include <renderer/materials/CheckerMaterial.h>

CheckerMaterial::CheckerMaterial() : CheckerMaterial(2, Vector(1.0,1.0,1.0), Vector(0.0,0.0,0.0))
{
}

CheckerMaterial::CheckerMaterial(int t, Vector odd, Vector even) : Material(0.4, 0.5, 0.3, 1.0)
{
	this->tessLevel = t;
	this->oddColor = Vector(odd);
	this->evenColor = Vector(even);
}

Vector CheckerMaterial::colorAtUV(double u, double v)
{
	bool odd = false;

	// Weird math I chugged out on paper. Scale [0,1] up to [0,t] to get numbers into
	// even intervals that correspond to checker patterns, then modulus to get even/odd.
	// U is horizonal, V is vertical. If V is "odd" then flip the odd/even bit, otherwise
	// the odd/even value for U is not changed.
	//
	// IE [0,0] = odd, [0,1] = even, [1,0] = even, [1,1] = odd

	float scaledU = u * tessLevel, scaledV = v * tessLevel;
	int floorU = int(scaledU), floorV = int(scaledV);

	if (floorU % 2 == 0)
		odd = true;

	if (floorV % 2 != 0)
		odd = !odd;

	if (odd)
		return this->oddColor;
	else
		return this->evenColor;
}
