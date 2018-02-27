#pragma once

#include "Color.h"
class MandelJuliaRenderer
{
public:
	MandelJuliaRenderer();
	~MandelJuliaRenderer();

	virtual Color computeColor(int iter, double preciseIter, double x, double y, double xPrime, double yPrime) = 0;
};

