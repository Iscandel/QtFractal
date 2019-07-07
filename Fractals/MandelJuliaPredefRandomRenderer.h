#pragma once
#include "MandelJuliaBaseRenderer.h"

#include "Parameters.h"

class MandelJuliaPredefRandomRenderer :
	public MandelJuliaBaseRenderer
{
public:
	MandelJuliaPredefRandomRenderer(const Parameters& params);
	~MandelJuliaPredefRandomRenderer();

	Color computeColor(int iter, double preciseIter, double x, double y, double xPrime, double yPrime);

protected:
	bool myIsLogLog;
	int myMaxIt;

	Color myFractalColor;
	std::vector<Color> myIterationsColors;
};

