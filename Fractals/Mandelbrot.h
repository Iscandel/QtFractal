#pragma once
#include "Fractal.h"

class Mandelbrot :
	public GenericParallelizableFractal
{
public:
	Mandelbrot(const Parameters& params= Parameters());
	~Mandelbrot();

	void computeFull(const Parameters& params);//, Array2D<Color>& out) override;

	Color computePixel(double x, double y, const Parameters& params) override;//, Array2D<Color>& out) override;

	void initRenderer(const std::string& renderer, const Parameters& params);

protected:
	bool escapesToInfinity(double a, double b, int& iterations, double& preciseIter);

	Color predefinedAndRandomRenderer(int iterations, double preciseIter);
	Color blackAndWhiteRenderer(int iterations, double preciseIter);
	Color sineRenderer(int iterations, double preciseIter, bool is3Dmode);

protected:
	bool myIsLogLog;
	int myMaxIt;
	std::string myRenderer;
	int myRefreshFrequency;

	double XMIN;
	double XMAX;
	double YMIN;
	double YMAX;

	Color myFractalColor;
	std::vector<Color> myIterationsColors;
	std::vector<double> myAmplitudes;
	std::vector<double> myPhases;
	std::vector<double> myPulsations;

	double mode3D;
	bool myIsMode3D;
};

