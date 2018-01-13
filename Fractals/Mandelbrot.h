#pragma once
#include "Fractal.h"

class Mandelbrot :
	public GenericParallelizableFractal
{
public:
	Mandelbrot();
	~Mandelbrot();

	void computeFull(const Parameters& params);//, Array2D<Color>& out) override;

	Color computePixel(double x, double y, const Parameters& params) override;//, Array2D<Color>& out) override;

protected:
	bool escapesToInfinity(double a, double b, int& iterations, double& preciseIter);

protected:
	bool myIsLogLog;
	int myMaxIt;
	int myRefreshFrequency;
};

