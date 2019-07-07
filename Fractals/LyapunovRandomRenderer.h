#pragma once
#include "LyapunovBaseRenderer.h"

#include "Parameters.h"

#include <vector>

class LyapunovRandomRenderer :
	public LyapunovBaseRenderer
{
public:
	LyapunovRandomRenderer(const Parameters& params);
	~LyapunovRandomRenderer();

	Color computeColor(double lambda) override;

protected:
	std::vector<Color> myColors;
};

