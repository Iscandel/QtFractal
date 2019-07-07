#include "LyapunovRandomRenderer.h"



LyapunovRandomRenderer::LyapunovRandomRenderer(const Parameters& params)
{
	std::vector<boost::any> tmp = params.getVector("lambdaColors", std::vector<boost::any>());
	for (auto elem : tmp) {
		myColors.push_back(boost::any_cast<Color>(elem));
	}
}


LyapunovRandomRenderer::~LyapunovRandomRenderer()
{
}

Color LyapunovRandomRenderer::computeColor(double lambda)
{
	double correctedLambda = lambda < 0 ? std::max(0., 1 + lambda) : std::min(1., 1 - lambda);

	if (!std::isfinite(correctedLambda))
		return Color();

	//The color ranges associated to lambda (which is [0-1]) depends on the number of colors
	double range = 1. / (myColors.size() - 1);
	//Select the appropriate part of the range
	int indexRange = correctedLambda / range;
	//Define the color range
	Color tmpCol = myColors[indexRange + 1] - myColors[indexRange];
	//Span lambda in the range [0-1]
	return myColors[indexRange] + (correctedLambda - (indexRange * range)) * (1 / range) * tmpCol;

	//if (correctedLambda < 0.5)
	//{
	//	Color tmpCol = col2 - col1;

	//	return col1 + correctedLambda * 2 * tmpCol;
	//}
	//else
	//{
	//	Color tmpCol = col3 - col2;
	//	return col2 + (correctedLambda - 0.5) * 2 * tmpCol;
	//}
}