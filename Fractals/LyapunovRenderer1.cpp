#include "LyapunovRenderer1.h"



LyapunovRenderer1::LyapunovRenderer1(const Parameters& params)
:myLambdaMin(-2.55)
,myLambdaMax(0.3959)
{
}


LyapunovRenderer1::~LyapunovRenderer1()
{

}

Color LyapunovRenderer1::computeColor(double lambda)
{
	double coeffR, coeffG, coeffB;

	if (lambda > 0) {
		coeffB = lambda / myLambdaMax;
		coeffR = coeffG = 0;
		coeffB = coeffB < 0. ? 0 : coeffB > 1. ? 1. : coeffB;
	}
	else
	{
		coeffR = 1 - std::pow(lambda / myLambdaMin, 2 / 3.0);
		coeffR = coeffR < 0. ? 0 : coeffR > 1. ? 1. : coeffR;
		coeffG = 1 - std::pow(lambda / myLambdaMin, 1 / 3.0);
		coeffG = coeffG < 0. ? 0 : coeffG > 1. ? 1. : coeffG;
		coeffB = 0;
	}

	return Color(coeffR, coeffG, coeffB);  //On crée la couleur avec les composantes RGB
}