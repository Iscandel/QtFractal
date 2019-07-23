#pragma once

#include "core/Color.h"
class MandelJuliaBaseRenderer
{
public:
	MandelJuliaBaseRenderer();
	~MandelJuliaBaseRenderer();

	virtual Color computeColor(int iter, double preciseIter, double x, double y, double xPrime, double yPrime) = 0;
};

