#include "MathUtil.hpp"

template<typename T>
inline T MathUtil::lerp(T x, T y, double t) {
	return x + (y - x) * t;
}

inline double MathUtil::deg2rad(double deg) {
	return deg * std::numbers::pi / 180.0f;
}

Eigen::Matrix4d MathUtil::rotateX(double deg) {
	Eigen::Matrix4d rotateMatrix = Eigen::Matrix4d::Identity();
	rotateMatrix <<
		1, 0, 0, 0,
		0, cos(MathUtil::deg2rad(deg)), -sin(MathUtil::deg2rad(deg)), 0,
		0, sin(MathUtil::deg2rad(deg)), cos(MathUtil::deg2rad(deg)), 0,
		0, 0, 0, 1;
	return rotateMatrix;
}

Eigen::Matrix4d MathUtil::rotateY(double deg) {
	Eigen::Matrix4d rotateMatrix = Eigen::Matrix4d::Identity();
	rotateMatrix <<
		cos(MathUtil::deg2rad(deg)), 0, sin(MathUtil::deg2rad(deg)), 0,
		0, 1, 0, 0,
		-sin(MathUtil::deg2rad(deg)), cos(MathUtil::deg2rad(deg)), 0,
		0, 0, 0, 1;
	return rotateMatrix;
}

Eigen::Matrix4d MathUtil::rotateZ(double deg) {
	Eigen::Matrix4d rotateMatrix = Eigen::Matrix4d::Identity();
	rotateMatrix <<
		cos(MathUtil::deg2rad(deg)), -sin(MathUtil::deg2rad(deg)), 0, 0,
		sin(MathUtil::deg2rad(deg)), cos(MathUtil::deg2rad(deg)), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1;
	return rotateMatrix;
}

Eigen::Matrix3d MathUtil::rotate(Eigen::Vector3d &n, double deg) {
	double rad = deg2rad(deg);
	Eigen::Matrix3d N;
	N << 0, -n.z(), n.y(),
		n.z(), 0, -n.x(),
		-n.y(), n.x(), 0;
	Eigen::Matrix3d rotateMatrix = cos(rad) * Eigen::Matrix3d::Identity() + (1 - cos(rad)) * n * n.transpose() + sin(rad) * N;

	return rotateMatrix;
}

Eigen::Matrix4d MathUtil::scale(double sx, double sy = 0, double sz = 0) {
	Eigen::Matrix4d scaleMatrix = Eigen::Matrix4d::Identity();
	scaleMatrix <<
		sx, 0, 0, 0,
		0, sy, 0, 0,
		0, 0, sz, 0,
		0, 0, 0, 1;

	return scaleMatrix;
}

Eigen::Matrix4d MathUtil::translate(Eigen::Vector3d &offset) {
	Eigen::Matrix4d translateMatrix = Eigen::Matrix4d::Identity();
	translateMatrix <<
		1, 0, 0, offset.x(),
		0, 1, 0, offset.y(),
		0, 0, 1, offset.z(),
		0, 0, 0, 1;

	return translateMatrix;
}

// RH
Eigen::Matrix4d MathUtil::lookat(Eigen::Vector3d &eyePos, Eigen::Vector3d &center, Eigen::Vector3d &up) {
	Eigen::Vector3d z = (center - eyePos).normalized(); 	// 方向向量
	Eigen::Vector3d x = z.cross(up).normalized(); 	// 右方向
	Eigen::Vector3d y = x.cross(z).normalized(); 	// 上方向

	Eigen::Matrix4d viewMatrix;
	viewMatrix << x[0], x[1], x[2], -x.dot(eyePos),
				  y[0], y[1], y[2], -y.dot(eyePos),
				  z[0], z[1], z[2], -z.dot(eyePos),
				  0, 0, 0, 1;

	return viewMatrix;
}


Eigen::Matrix4d MathUtil::getModelMatrix(double rotationAngle) {

}

// 正交
Eigen::Matrix4d MathUtil::getOrthoMatrix(double t, double b, double l, double r, double n, double f) {
	Eigen::Matrix4d scaleMatrix = MathUtil::scale(2.0 / (t - b), 2.0 / (t - b), 2.0 / (n - f));
	Eigen::Vector3d offset;
	offset << -(r + l) / 2,
			 -(t + b) / 2,
			 -(n + f) / 2;
	Eigen::Matrix4d translateMatrix = MathUtil::translate(offset);
	return scaleMatrix * translateMatrix;
}

Eigen::Matrix4d MathUtil::getProjectionMatrix(double eyeFoV, double aspectRatio, double zNear, double zFar) {
	Eigen::Matrix4d persp2ortho = Eigen::Matrix4d::Identity();
	persp2ortho << 	zNear, 0, 0, 0,
					0, zNear, 0, 0,
					0, 0, zNear + zFar, -zNear * zFar,
					0, 0, 0, 1;
	double t = tan(MathUtil::deg2rad(eyeFoV / 2.0)) * abs(zNear);
	double b = -t;
	double r = t * aspectRatio;
	double l = -r;

	Eigen::Matrix4d orthoMatrix = MathUtil::getOrthoMatrix(t, b, l, r, zNear, zFar);

	return orthoMatrix * persp2ortho;
}

Eigen::Matrix4d getViewPortMatrix(double width, double height) {
	Eigen::Matrix4d viewPortMatrix;
	viewPortMatrix << width / 2.0, 0, 0, width / 2.0,
					  0, height / 2.0, 0, height / 2.0,
					  0, 0, 1, 0,
					  0, 0, 0, 1;
	return viewPortMatrix;
}

