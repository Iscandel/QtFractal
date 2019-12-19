#pragma once

#include "core/Parameters.h"
#include "core/Types.h"
#include "tools/WithSmartPtr.h"

#include <Eigen/Core>
#include <Eigen/Geometry>

class Camera : public WithSmartPtr<Camera>
{
public:
	Camera() {
		auto tmp = Eigen::Affine2d::Identity();
		setWorldTransform(tmp);
	}
	Camera(const Parameters&);
	~Camera();

	virtual Point2r getIndexSpacePoint(real a, real b) = 0;
	virtual Point2r getWorldSpacePoint(real x, real y) = 0;

	void setWorldTransform(Eigen::Affine2d& transform) { myTransform = transform; }
	void setSize(int width, int height) { myWidth = width; myHeight = height;}

protected:
	Eigen::Affine2d myTransform;
	int myWidth;
	int myHeight;
};

