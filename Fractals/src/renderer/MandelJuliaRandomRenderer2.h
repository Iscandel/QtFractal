#pragma once
#include "MandelJuliaBaseRenderer.h"

#include "core/Parameters.h"

class MandelJuliaRandomRenderer2 :
	public MandelJuliaBaseRenderer
{
public:
	MandelJuliaRandomRenderer2(const Parameters& params);
	~MandelJuliaRandomRenderer2();

	Color computeColor(int iter, double preciseIter, double x, double y, double xPrime, double yPrime) override;

protected:
	bool myIsLogLog;
	int myMaxIt;

	Color myFractalColor;
	std::vector<Color> myIterationsColors;

	bool myIsCyclicLastToFirst;
};

