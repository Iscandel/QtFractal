#pragma once
#include "Fractal.h"
#include "Image.h"
#include "Job.h"
#include "Parameters.h"

class GenericFractalJob :
	public Job
{
public:
	GenericFractalJob(int offsetX, int offsetY, int sizeX, int sizeY, GenericParallelizableFractal* fractal, const Parameters& params, Image::ptr image);//, int witdh, int height);
	~GenericFractalJob();

	void run() override;
protected:
	GenericParallelizableFractal* myFractal;
	Parameters myParameters;

	int myOffsetX;
	int myOffsetY;
	int mySizeX;
	int mySizeY;
	bool myIsFinished;
	Image::ptr myImage;
	//int myWidth;
	//int myHeight;
};




