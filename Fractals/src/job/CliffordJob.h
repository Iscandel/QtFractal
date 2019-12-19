#pragma once

#include "Job.h"
#include "core/Image.h"
#include "core/Parameters.h"

class Clifford;

class CliffordJob : public Job
{
public:
	CliffordJob(int offsetX, int offsetY, int sizeX, int sizeY, Clifford* fractal, const Parameters& params, Image::ptr imageRed, Image::ptr imageGreen, Image::ptr imageBlue);//Image::ptr image);
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
	Image::ptr myImage;

	std::shared_ptr<Image> myImageRed;
	std::shared_ptr<Image> myImageGreen;
	std::shared_ptr<Image> myImageBlue;
};

