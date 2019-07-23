#pragma once

#include "Job.h"
#include "core/Image.h"
#include "core/Parameters.h"

class Buddhabrot;

class BuddhabrotJob : public Job
{
public:
	BuddhabrotJob(int offsetX, int offsetY, int sizeX, int sizeY, Buddhabrot* fractal, const Parameters& params, Image::ptr imageRed, Image::ptr imageGreen, Image::ptr imageBlue);//Image::ptr image);
	~BuddhabrotJob();

	void run() override;

protected:
	Buddhabrot* myFractal;

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

