#pragma once
#include "Camera.h"
class OrthographicCamera :
	public Camera
{
public:
	OrthographicCamera();
	~OrthographicCamera();

	Point2r getWorldSpacePoint(real x, real y) override;
};

