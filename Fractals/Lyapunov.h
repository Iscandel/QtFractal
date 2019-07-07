#pragma once
#include "Fractal.h"

#include "LyapunovBaseRenderer.h"
#include "Rng.h"

class Lyapunov :
	public GenericParallelizableFractal
{
public:
	Lyapunov(const Parameters& params);
	~Lyapunov();

	Color computePixel(double x, double y, const Parameters& params, ParserById& parserById) override;

	void initRenderer(const std::string& renderer, const Parameters& params);

protected:
	double getCoefficient(int index, double a, double b);

	Color rendu1(double lambda);
	Color rendu2(double lambda);
	Color rendu3(double lambda);
protected:
	int myMaxIt;
	int myRefreshFrequency;
	double myInitialValue;

	std::string myStrRenderer;

	//double XMIN;
	//double XMAX;
	//double YMIN;
	//double YMAX;

	std::string mySequence;
	std::vector<Color> myColors;
	Rng myRng;

	std::unique_ptr<LyapunovBaseRenderer> myRenderer;
};

