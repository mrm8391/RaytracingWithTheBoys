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

	/*
	Return a camera view transform http://www.codinglabs.net/article_world_view_projection_matrix.aspx

	(Column major)
	[ [X.x, x.y, x.z, 0]
	  [Y.x, Y.y, Y.z, 0]
	  [Z.x, Z.y, Z.z, 0]
	  [t.x, t.y, t.z, 1] ]

	@param X X-axis of camera space in world coordinates
	@param Y Y-axis of camera space in world coordinates
	@param Z Z-axis of camera space in world coordinates
	@param t Translation to camera position
	*/
	static Eigen::Matrix4d viewTransform(
		Eigen::Vector3d X,
		Eigen::Vector3d Y,
		Eigen::Vector3d Z,
		Eigen::Vector3d t
	);

private:
	//Private constructor to prevent initialization
	Transforms();
};

#endif