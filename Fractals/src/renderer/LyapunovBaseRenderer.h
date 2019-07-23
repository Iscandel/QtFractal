#pragma once

#include "core/Color.h"

class LyapunovBaseRenderer
{
public:
	LyapunovBaseRenderer();
	~LyapunovBaseRenderer();

	virtual Color computeColor(double lambda) = 0;
};

