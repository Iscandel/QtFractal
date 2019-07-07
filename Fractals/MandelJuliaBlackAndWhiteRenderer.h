#pragma once
#include "MandelJuliaBaseRenderer.h"

#include "Parameters.h"

class MandelJuliaBlackAndWhiteRenderer :
	public MandelJuliaBaseRenderer
{
public:
	MandelJuliaBlackAndWhiteRenderer(const Parameters& params);
	~MandelJuliaBlackAndWhiteRenderer();

	Color computeColor(int iter, double preciseIter, double x, double y, double xPrime, double yPrime);

protected:
	bool myIsLogLog;
	int myMaxIt;

	Color myFractalColor;
};

