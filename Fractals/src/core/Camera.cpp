#include "Camera.h"



Camera::Camera(const Parameters& params)
{
	auto tmp = Eigen::Affine2d::Identity();
	setWorldTransform(tmp);
}


Camera::~Camera()
{
}
