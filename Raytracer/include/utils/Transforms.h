/*
Utility class for defining common matrix transformations.

Not meant to be initialized, functions are static.
*/

#ifndef RT_TRANSFORMS_H
#define RT_TRANSFORMS_H

#include <Eigen/Core>

class Transforms {

public:
	/*
	Return a rotation transformation matrix. 
	*/
	static Eigen::Matrix4d rotate(double rx, double ry, double rz);

	/*
	Return a scaling transformation matrix.
	*/
	static Eigen::Matrix4d scale(double sx, double sy, double sz);

	/*
	Return a translation transformation matrix.
	*/
	static Eigen::Matrix4d translate(double dx, double dy, double dz);

private:
	//Private constructor to prevent initialization
	Transforms();
};

#endif