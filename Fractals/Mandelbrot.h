#pragma once
#include "Fractal.h"

class Mandelbrot :
	public Fractal
{
public:
	Mandelbrot();
	~Mandelbrot();

	void compute(const Parameters& params) override;//, Array2D<Color>& out) override;

protected:
	bool escapesToInfinity(double a, double b, int& iterations, double& preciseIter);

protected:
	bool myIsLogLog;
	int myMaxIt;
	int myRefreshFrequency;
};

