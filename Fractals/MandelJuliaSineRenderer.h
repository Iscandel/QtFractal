#pragma once
#include "MandelJuliaBaseRenderer.h"

#include <vector>

#include "Parameters.h"

class MandelJuliaSineRenderer :
	public MandelJuliaBaseRenderer
{
public:
	MandelJuliaSineRenderer(const Parameters& params);
	~MandelJuliaSineRenderer();

	Color computeColor(int iter, double preciseIter, double x, double y, double xPrime, double yPrime);

protected:
	bool myIs3DMode;
	Color myFractalColor;
	std::vector<Color> myIterationsColors;
	std::vector<double> myAmplitudes;
	std::vector<double> myPhases;
	std::vector<double> myPulsations;

	int myMaxIt;
};

