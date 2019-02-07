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
	static Eigen::Matrix4d rotate(double x, double y, double z);

private:
	//Private constructor to prevent initialization
	Transforms();
};

#endif