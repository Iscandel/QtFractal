#include "MandelJuliaRandomRenderer2.h"



MandelJuliaRandomRenderer2::MandelJuliaRandomRenderer2(const Parameters& params)
	:myIsCyclicLastToFirst(true)
{
	myIsLogLog = params.getBool("logLog", false);
	myMaxIt = params.getInt("maxIter", 100);

	myFractalColor = params.getColor("fractalColor", Color());
	std::vector<boost::any> tmp = params.getVector("iterationColors", std::vector<boost::any>());
	for (auto elem : tmp) {
		myIterationsColors.push_back(boost::any_cast<Color>(elem));
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
MandelJuliaRandomRenderer2::~MandelJuliaRandomRenderer2()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Color MandelJuliaRandomRenderer2::computeColor(int iterations, double preciseIter, double x, double y, double xPrime, double yPrime)
{
	if (std::isnan(preciseIter) || std::isinf(preciseIter))
	{
		std::cout << "Renderer nan value" << std::endl;
		return Color();
	}

	if (iterations == myMaxIt)
		return myFractalColor;

	//Normalize iterations by maxIt
	double correctedIt;
	if (myIsLogLog)
		correctedIt = (preciseIter);// / (double)myMaxIt);
	else
		correctedIt = (preciseIter);// / (double)myMaxIt);

	if (correctedIt > 1.)
	{
		if ((int)correctedIt % 2 == 1 && !myIsCyclicLastToFirst)
			correctedIt = 1. - (correctedIt - (int)correctedIt); //This line is for cyclic "last -> reverse come back -> first -> forward..."
		else
			correctedIt = correctedIt - (int)correctedIt;
	}

	//The color ranges associated to lambda (which is [0-1]) depending on the number of colors
	double range = myIsCyclicLastToFirst ? 1. / myIterationsColors.size() : 1. / (myIterationsColors.size() - 1);
	//Select the appropriate part of the range
	int indexRange = correctedIt / range;
	//Define the color range
	Color colorRange;
	if(myIsCyclicLastToFirst)
		colorRange = myIterationsColors[indexRange + 1 == myIterationsColors.size() ? 0 : indexRange + 1] - myIterationsColors[indexRange];
	else
		colorRange = myIterationsColors[indexRange + 1] - myIterationsColors[indexRange];
	//Span lambda in the range [0-1]
	return myIterationsColors[indexRange] + (correctedIt - (indexRange * range)) * (1 / range) * colorRange;
}