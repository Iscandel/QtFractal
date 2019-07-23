#pragma once
#include "Fractal.h"

#include "renderer/MandelJuliaBaseRenderer.h"

//#include <complex>

#include "core/Complex.h"

#include <complex>
#define FP_SUPPORT_COMPLEX_DOUBLE_TYPE
#include <sol.hpp>
#include "exprtk.hpp"
#include "FParser\fparser.hh"

//Layer : 1 type de calcul + 1 renderer
class Mandelbrot :
	public GenericParallelizableFractal
{
public:
	enum ParserType
	{
		FUNCTION,
		ADDEND_FUNCTION,
		VALUE_RERANGE,
		RERANGE_3D_HEIGHT
	};

	enum ComputeMandelbrot
	{
		ITERATIONS = 1,
		TRIANGLE_INEQUALITY = 2,
		AVERAGE_CURVATURE_1 = 4,
		AVERAGE_CURVATURE_2 = 8,
		AVERAGE_CURVATURE_3 = 16,
		STRIPE_AVERAGE = 32,
		FOLD_LINE = 64,
		FOLD_SQUARE = 128,
		FOLD_CIRCLE = 256,
		FOLD_EXP_SMOOTHING = 512,
		FOLD_Z_SMOOTHING = 1024,
		STOP = 2048,
		BRANCHING = TRIANGLE_INEQUALITY | AVERAGE_CURVATURE_1 | AVERAGE_CURVATURE_2 | AVERAGE_CURVATURE_3 | STRIPE_AVERAGE,
		FOLD = FOLD_LINE | FOLD_SQUARE | FOLD_CIRCLE | FOLD_EXP_SMOOTHING | FOLD_Z_SMOOTHING,
		ADDEND = BRANCHING | FOLD
	};

public:
	Mandelbrot(const Parameters& params= Parameters());
	~Mandelbrot();

	//void computeFull(const Parameters& params);//, Array2D<Color>& out) override;

	Color computePixel(double x, double y, const Parameters& params, ParserById& parserById) override;//, Array2D<Color>& out) override;

	void initRenderer(const std::string& renderer, const Parameters& params);

	void computeBranching(int iterations, double x, double y, double xnew, double ynew, double a, double b,
		double& prevSum, double& sum, int& skipLastIterBranching, ComplexD& znpprev, ComplexD& znPrev, std::map<int, MathParser>& parserById);

	void normalizeBranching(int iterations, int skipLastIter, double& sum, double& prevSum);

	Color compute3D(double a, double b, double x, double y, double xPrime, double yPrime, int iterations, double preciseIter, double addEndMeanSum, ParserById& parserById);

	double rerange3DHeight(double value, ParserById& parserById);
protected:
	bool escapesToInfinity(double a, double b, int& iterations, double& preciseIter, double& x, double& y, double& xPrime, double& yPrime, double& sum, ParserById& parserById);

	Color predefinedAndRandomRenderer(int iterations, double preciseIter);
	Color blackAndWhiteRenderer(int iterations, double preciseIter);
	Color sineRenderer(int iterations, double preciseIter, bool is3Dmode);

protected:
	bool myIsLogLog;
	int myMaxIt;
	std::string myStrRenderer;
	int myRefreshFrequency;

	double myBailout;

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

	std::unique_ptr<MandelJuliaBaseRenderer> myRenderer;


	//double sum;

	//Complex<double> znprev;

	double myStripeDensity;

	ComputeMandelbrot myComputationType;

	double myBrightnessFactor;

	bool myIsLambertCorrection;

	int myWidth;
	int myHeight;

	//
	sol::state lua;
	//ComplexD point;
	//ComplexD z;
	//

	//
	exprtk::expression<double> expression;
	exprtk::expression<double> expression2;
	double myx, myy, mya, myb;
	//

	//
	//FunctionParserBase<std::complex<double> > fp;
	FunctionParser_cd fp;
};

