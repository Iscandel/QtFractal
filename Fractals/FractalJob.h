#pragma once
#include "Fractal.h"
#include "Job.h"
#include "Parameters.h"

class FractalJob :
	public Job
{
public:
	FractalJob(Fractal::ptr fractal, const Parameters& params, int witdh, int height);
	~FractalJob();

	void run() override;
protected:
	Fractal::ptr myFractal;
	Parameters myParameters;
	int myWidth;
	int myHeight;
};




