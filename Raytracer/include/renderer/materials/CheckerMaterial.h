/*
Procedural checkerboard texture. Intended for use with triangles/squares.
May look strange if using a non-right triangle
*/

#include <renderer/materials/Material.h>

#ifndef RT_CHECKER_H
#define RT_CHECKER_H

class CheckerMaterial : public Material {

public:
	
	CheckerMaterial();

	/*
	Construct checker material. Set specular color and phong constants in superclass (setPhong) to manually alter shading constants.

	@param t Number of levels for the checker pattern. t=2 would be a 2x2 checker pattern.
	@param odd Color for odd occurring squares
	@param even Color for even occurring squares
	*/
	CheckerMaterial(int t, Vector odd, Vector even);

	//tessellation level of checker pattern
	double tessLevel;

	//Colors to occur for each checker alteration
	Vector oddColor, evenColor;

	/*
	Corresponding color in the checker pattern. Depends on tessLevel.

	@param u,v UV mapping, expects [0,1] for both.
	*/
	virtual Vector colorAtUV(double u, double v);

};

#endif