#pragma once
#include "Camera.h"
class OrthographicCamera :
	public Camera
{
public:
	OrthographicCamera();
	~OrthographicCamera();

	Point2r getIndexSpacePoint(real a, real b) override;
	Point2r getWorldSpacePoint(real x, real y) override;
};

