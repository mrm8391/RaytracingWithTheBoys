
#include <Eigen/Core>
#include <Eigen/Geometry>

#include <utils/Transforms.h>

using Eigen::Matrix4d;
using Eigen::Transform;
using Eigen::Scaling;
using Eigen::Translation;

Matrix4d Transforms::rotate(double rx, double ry, double rz)
{
	Matrix4d rot;
	
	//worry about this later

	return rot;
}

Eigen::Matrix4d Transforms::scale(double sx, double sy, double sz)
{
	Transform<double, 3, Eigen::Affine> t;
	t = Scaling<double>(sx, sy, sz);

	return t.matrix();
}

Eigen::Matrix4d Transforms::translate(double dx, double dy, double dz)
{
	Transform<double, 3, Eigen::Affine> t;
	Eigen::Vector3d dX;
	dX << dx, dy, dz;

	t = Translation<double, 3>(dX);

	return t.matrix();
}

Eigen::Matrix4d Transforms::viewTransform(Eigen::Vector3d X, Eigen::Vector3d Y, Eigen::Vector3d Z, Eigen::Vector3d t)
{
	//Construct a matrix using Eigen's block operations to splice
	//the vectors in. Can't use nicer syntax since we're converting
	//3d vectors into a 4d matrix, but this gets optimized by compiler
	Matrix4d m;
	m.block<3, 1>(0, 0) = X;
	m.block<3, 1>(0, 1) = Y;
	m.block<3, 1>(0, 2) = Z;
	m.block<3, 1>(0, 3) = t;

	//Set bottom row and homogeneous coordinate
	m(3, 0) = 0;
	m(3, 1) = 0;
	m(3, 2) = 0;
	m(3, 3) = 1;

	return m;
}
