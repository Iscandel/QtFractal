#pragma once

#include "Color.h"

class LyapunovBaseRenderer
{
public:
	LyapunovBaseRenderer();
	~LyapunovBaseRenderer();

	virtual Color computeColor(double lambda) = 0;
};

