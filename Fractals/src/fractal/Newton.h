#pragma once
#include "Fractal.h"

#include "core/Rng.h"

#include <complex>
#include <vector>

class Newton :
	public GenericParallelizableFractal
{
	REGISTER_FRACTAL_PRATICAL_NAME(Newton)
public:
	typedef std::complex<double> complexD;

public:
	Newton(const Parameters& params = Parameters());
	~Newton();

	Color computePixel(double x, double y, const Parameters& params, ParserById& parserById) override;//, Array2D<Color>& out) override;

	void initRenderer(const std::string& renderer, const Parameters& params);

protected:
	complexD computeFDeZ(const complexD& Z, const std::vector<complexD>& roots);
	complexD derived(const complexD& Z, const std::vector<complexD>& roots);

	Color rendu1(double a, double b, int indexColor, int iterations, double preciseIterations);
	Color rendu2(double a, double b, int indexColor, int iterations, double preciseIterations);
	Color rendu3(double a, double b, int indexColor, int iterations, double preciseIterations);

protected:
	//std::unique_ptr<MandelJuliaBaseRenderer> myRenderer;

	int myMaxIter;

	std::vector<complexD> myZeros;
	std::vector<complexD> myPoles;

	std::vector<Color> myColors;

	Rng myRng;
};

