#include "Lyapunov.h"

#include "LyapunovRandomRenderer.h"
#include "LyapunovRenderer1.h"
#include "ObjectFactoryManager.h"

#include <vector>

Lyapunov::Lyapunov(const Parameters& params)
:myMaxIt(params.getInt("maxIter", 100))
,myRefreshFrequency(10)
,mySequence(params.getString("sequence", "ab"))
,myInitialValue(params.getDouble("initialValue", 0.5))
,myStrRenderer(params.getString("renderer", "Predefined 1"))

{
	//mySequence = "bbbbbbaaaaaa";//"ab";//;
	myRng.seed(time(NULL));
	int nbColors = 3;
	myColors.resize(nbColors);
	for (int i = 0; i < nbColors; i++)
	{
		myColors[i] = Color(myRng.nextDouble(), myRng.nextDouble(), myRng.nextDouble());
	}

	initRenderer(myStrRenderer, params);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Lyapunov::~Lyapunov()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Lyapunov::initRenderer(const std::string& renderer, const Parameters& params)
{
	if (renderer == "Predefined 1")
	{
		myRenderer = std::make_unique<LyapunovRenderer1>(params);
	}
	else if (renderer == "Random")
	{
		myRenderer = std::make_unique<LyapunovRandomRenderer>(params);
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Color Lyapunov::computePixel(double a, double b, const Parameters& params, ParserById& parserById)
{
	double P = myInitialValue;
	double k;
	double exponent = 0;

	for (int i = 0; i < myMaxIt; i++)
	{
		k = getCoefficient(i, a, b);
		P = k * P * (1 - P);
	}

	double product = 1.;
	for (int i = 0; i < myMaxIt; i++)
	{
		k = getCoefficient(i, a, b);

		P = k * P * (1 - P);

		product *= k * (1 - 2 * P);
		exponent += std::log(std::abs(k * (1 - 2 * P)));
		//exponent += std::log(std::abs(product));
	}

	
	exponent /= myMaxIt;// *mySequence.size();
	//if(exponent > 1)
	//std::cout << exponent << std::endl;
	double lambda = exponent;

	double coeffR, coeffG, coeffB;
	double lambda_min = -2.55;    //Définie pour le rendu de couleurs 2
	double lambda_max = 0.3959;   //Définie pour le rendu de couleurs 2

	return myRenderer->computeColor(lambda);
	//return rendu3(lambda);

	//if (lambda > 0) {
	//	//return Color(lambda);
	//	if(std::isfinite(lambda))
	//		return Color(std::sin(1.15 * lambda + 0.4), std::sin(1.365 * lambda + 0.1), std::sin(1.24 * lambda + 0.2));
	//	return Color();
	//	coeffB = lambda / lambda_max;
	//	coeffR = coeffG = 0;
	//	coeffB = coeffB < 0. ? 0 : coeffB > 1. ? 1. : coeffB;
	//}
	//else
	//{
	//	//return Color(-lambda);
	//	if (std::isfinite(lambda))
	//		return Color(std::sin(-1.24 * lambda + 0.14), std::sin(-1.547 * lambda + 0.051), std::sin(-1.0489 * lambda + 0.12));
	//	return Color();
	//	coeffR = 1 - std::pow(lambda / lambda_min, 2 / 3.0);
	//	coeffR = coeffR < 0. ? 0 : coeffR > 1. ? 1. : coeffR;
	//	coeffG = 1 - std::pow(lambda / lambda_min, 1 / 3.0);
	//	coeffG = coeffG < 0. ? 0 : coeffG > 1. ? 1. : coeffG;
	//	coeffB = 0;
	//}

	//return Color(coeffR, coeffG, coeffB);  //On crée la couleur avec les composantes RGB
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
double Lyapunov::getCoefficient(int index, double a, double b)
{
	char c = mySequence[index % mySequence.size()];
	if (c == 'a')
		return a;
	else
		return b;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Color Lyapunov::rendu1(double lambda)
{
	double coeffR, coeffG, coeffB;
	double lambda_min = -2.55;    //Définie pour le rendu de couleurs 2
	double lambda_max = 0.3959;   //Définie pour le rendu de couleurs 2

	if (lambda > 0) {
		coeffB = lambda / lambda_max;
		coeffR = coeffG = 0;
		coeffB = coeffB < 0. ? 0 : coeffB > 1. ? 1. : coeffB;
	}
	else
	{
		coeffR = 1 - std::pow(lambda / lambda_min, 2 / 3.0);
		coeffR = coeffR < 0. ? 0 : coeffR > 1. ? 1. : coeffR;
		coeffG = 1 - std::pow(lambda / lambda_min, 1 / 3.0);
		coeffG = coeffG < 0. ? 0 : coeffG > 1. ? 1. : coeffG;
		coeffB = 0;
	}

	return Color(coeffR, coeffG, coeffB);  //On crée la couleur avec les composantes RGB
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Color Lyapunov::rendu2(double lambda)
{
	if (lambda > 0) {
		//return Color(lambda);
		if (std::isfinite(lambda))
			return Color(std::sin(1.15 * lambda + 0.4), std::sin(1.365 * lambda + 0.1), std::sin(1.24 * lambda + 0.2));
		return Color();
	}
	else
	{
		//return Color(-lambda);
		if (std::isfinite(lambda))
			return Color(std::sin(-1.24 * lambda + 0.14), std::sin(-1.547 * lambda + 0.051), std::sin(-1.0489 * lambda + 0.12));
		return Color();
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Color Lyapunov::rendu3(double lambda)
{
	Color col1(0.9, 0.9, 0.1);
	Color col2(0.1, 0.9, 0.1);
	Color col3(0.1, 0.1, 0.9);

	double correctedLambda = lambda < 0 ? std::max(0., 1 + lambda) : std::min(1., 1-lambda);

	if (!std::isfinite(correctedLambda))
		return Color();

	//The color ranges associated to lambda (which is [0-1]) depends on the number of colors
	double range = 1. / (myColors.size() - 1);
	//Select the appropriate part of the range
	int indexRange = correctedLambda / range;
	//Define the color range
	Color tmpCol = myColors[indexRange + 1] - myColors[indexRange];
	//Span lambda in the range [0-1]
	return myColors[indexRange] + (correctedLambda  - (indexRange * range)) * (1 / range) * tmpCol;

	if (correctedLambda < 0.5)
	{
		Color tmpCol = col2 - col1;

		return col1 + correctedLambda * 2  * tmpCol;
	}
	else
	{
		Color tmpCol = col3 - col2;
		return col2 + (correctedLambda - 0.5) * 2 * tmpCol;
	}
}

FACTORY_REGISTER_TYPE(Lyapunov, Fractal)