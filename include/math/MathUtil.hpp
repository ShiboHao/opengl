#pragma once

#include <Eigen/Eigen>
#include <Eigen/Dense>

#include <cmath>
#include <numbers>


namespace MathUtil {

	//插值
	template<typename T>
	inline T lerp(T x, T y, double t);

	// 角度转弧度
	inline double deg2rad(double deg);

	Eigen::Matrix4d scale(double sx, double sy, double sz);

	// Rodrigue's Rotation Formula
	// n 过原点轴
	Eigen::Matrix3d rotate(Eigen::Vector3d &n, double deg);
	Eigen::Matrix4d rotateX(double deg);
	Eigen::Matrix4d rotateY(double deg);
	Eigen::Matrix4d rotateZ(double deg);

	Eigen::Matrix4d translate(Eigen::Vector3d &offset);

	Eigen::Matrix4d lookat(Eigen::Vector3d &eyePos, Eigen::Vector3d &target, Eigen::Vector3d &up);
	// 视图矩阵
	Eigen::Matrix4d getViewMatrix(Eigen::Vector3d &eyePos);

	Eigen::Matrix4d getModelMatrix(double rotationAngle);

	// 正交
	Eigen::Matrix4d MathUtil::getOrthoMatrix(double t, double b, double l, double r, double n, double f);

	Eigen::Matrix4d getProjectionMatrix(double eyeFoV, double aspectRatio, double zNear, double zFar);

	Eigen::Matrix4d getViewPortMatrix(double width, double height);

	// bool isInsideTriangle(Eigen::Vector3d& point, )
}
