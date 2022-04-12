#include "MandelJuliaSineRenderer.h"



MandelJuliaSineRenderer::MandelJuliaSineRenderer(const Parameters& params)
{
	myMaxIt = params.getInt("maxIter", 100);

	myFractalColor = params.getColor("fractalColor", Color());
	myIs3DMode = params.getBool("isMode3D", false);
	std::vector<std::any> tmp = params.getVector("amplitudes", std::vector<std::any>());
	for (auto elem : tmp)
		myAmplitudes.push_back(std::any_cast<double>(elem));

	tmp = params.getVector("phases", std::vector<std::any>());
	for (auto elem : tmp)
		myPhases.push_back(std::any_cast<double>(elem));

	tmp = params.getVector("pulsations", std::vector<std::any>());
	for (auto elem : tmp)
		myPulsations.push_back(std::any_cast<double>(elem));

}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
MandelJuliaSineRenderer::~MandelJuliaSineRenderer()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Color MandelJuliaSineRenderer::computeColor(int iter, double preciseIter, double x, double y, double xPrime, double yPrime)
{
	double reDiv = x*xPrime + y*yPrime;
	double imDiv = x*yPrime - y*xPrime;

	double mode3D = (double)std::atan2(imDiv, reDiv);

	Color fractal;

	if (iter == myMaxIt)
		return myFractalColor;

	if (!myIs3DMode)
	{
		double rouge = 0, vert = 0, bleu = 0;

		double a = 0.5;
		double b = 0.5;
		double it = preciseIter / myMaxIt * 2.718;

		double r = a + b * std::sin(2 * 3.1415 * (std::log(it) + 0.));
		double g = a + b * std::sin(2 * 3.1415 * (std::log(it) + 0.33));
		double bl = a + b * std::sin(2 * 3.1415 * (std::log(it) + 0.67));

		//double r = (double)(myAmplitudes[0] * std::sin(myPulsations[0] * preciseIter + myPhases[0]));
		//double g = (double)(myAmplitudes[1] * std::sin(myPulsations[1] * preciseIter + myPhases[1]));
		//double bl = (double)(myAmplitudes[2] * std::sin(myPulsations[2] * preciseIter + myPhases[2]));

		fractal = Color(r, g, bl);   //On crée la couleur
	}
	else
	{
		double rouge = 0, vert = 0, bleu = 0;

		double r = (double)(myAmplitudes[0] * std::sin(myPulsations[0] * mode3D + myPhases[0]));
		double g = (double)(myAmplitudes[1] * std::sin(myPulsations[1] * mode3D + myPhases[1]));
		double bl = (double)(myAmplitudes[2] * std::sin(myPulsations[2] * mode3D + myPhases[2]));

		fractal = Color(r, g, bl);   //On crée la couleur
	}

	return fractal;
}