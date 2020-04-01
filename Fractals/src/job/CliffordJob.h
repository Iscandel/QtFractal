#pragma once

#include "Job.h"

#include "core/Camera.h"
#include "core/Image.h"
#include "core/Parameters.h"

class Clifford;

class CliffordJob : public Job
{
public:
	CliffordJob(int offsetX, int offsetY, int sizeX, int sizeY, Clifford* fractal, const Parameters& params, 
			Camera::ptr camera, int maxIt, real scale, Image::ptr imageRes, const Color& col);
	~CliffordJob();

	void run() override;

protected:
	Clifford* myFractal;

	Parameters myParameters;

	int myOffsetX;
	int myOffsetY;
	int mySizeX;
	int mySizeY;
	bool myIsFinished;
	Image::ptr myImageRes;
	Camera* myCamera;
	int myMaxIt;
	real myScale;
	Color myColor;

};

