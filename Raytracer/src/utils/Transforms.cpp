
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
