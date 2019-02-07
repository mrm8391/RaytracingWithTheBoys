/*
Matrix representation, may be replaced with a library later.
*/

#ifndef RT_MATRIX_H
#define RT_MATRIX_H

#include <Eigen/Core>

class Matrix {

public:
	Matrix();

	Eigen::Matrix4d matr;
};

#endif