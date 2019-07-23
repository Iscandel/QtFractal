#include "Newton.h"

#include "ObjectFactoryManager.h"


Newton::Newton(const Parameters& params)
{
	myMaxIter = 500;
	myZeros = std::vector<complexD>{ {-0.5, 0.866}, {-0.5, -0.866}, {1, 0} };
	myPoles = std::vector<complexD>{ { 2.04, -0.489 },{ -0.155, 3.6 },{ 1.69, 0.5 } };
	for (int i = 0; i < myZeros.size() + myPoles.size(); i++)
	{
		myColors.push_back(Color(myRng.nextDouble(), myRng.nextDouble(), myRng.nextDouble()));
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Newton::~Newton()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
//Complex sequence defined by Newton  : zn+1=zn - f(z)/f'(z)
Color Newton::computePixel(double a, double b, const Parameters & params, ParserById& parserById)
{
	complexD z = complexD(a, b);
	//Complexe FDeZ = new Complexe(Z.soustraction(zeros[0]));  //premier terme vaut (z-z1)
	//Complexe FDeZP = new Complexe(1,0); 
	complexD fPrimeDeZ;
	complexD fPrimeDeP;
	int iterations = 0;

	complexD fDeZ(z - myZeros[0]);
	complexD fDeZP(1, 0);

	fDeZ = computeFDeZ(z, myZeros);   //Recompute "f(z)" for the numerator
	if (myPoles.size() != 0)
		fDeZP = computeFDeZ(z, myPoles);   //On recalcule "f(z)" POUR LE DENOMINATEUR

								  //FDeZ = FDeZ.division(FDeZP);
								  /*Compute f'(z)*/
								  /*We have (z-z1)(z-z2)...(z-zn). Product derivative of (uvw...z)' is :
								  * u'vw..z + uv'w...z + ... + uvw...z'
								  * That is for the numerator and denom, separately.
								  * For the resulting quotient, we have
								  * f' = (u'v - uv') / v ²*/

	complexD Temp;
	fPrimeDeZ = (derived(z, myZeros) * fDeZP - derived(z, myPoles) * fDeZ) / (fDeZP * fDeZP);	//Recompute f'(z)
	
	int indexColor = 0;
	bool found = false;
	double preciseAdvance = 0;
	double previousMean = 10000;
	double mean = 0;
	complexD previousZ;
	while (iterations < myMaxIter)
	{
		complexD Tmp;

		z = z - fDeZ / fPrimeDeZ;//Divide f(z)/f'(z)

		fDeZ = computeFDeZ(z, myZeros);   //Recompute f(z)

		//if (rendu == 2)
		{
			if (myPoles.size() != 0)
				fDeZP = computeFDeZ(z, myPoles);   //Recompute "f(z)" for denom
			fDeZ = fDeZ / fDeZP;
		}

		fPrimeDeZ = (derived(z, myZeros) * fDeZP - derived(z, myPoles) * fDeZ) / (fDeZP * fDeZP);	//Recompute f'(z)

		
		/*Check the convergence of the sequence to any of the zeros or poles*/
		double eps = 1e-2;
		for (int j = 0; j < myZeros.size();j++)
		{
			if(std::norm(z - myZeros[j]) < eps)
			//if (std::abs((z.real() - myZeros[j].real())) < eps &&
			//	std::abs((z.imag() - myZeros[j].imag())) < eps)
			{
				indexColor = j;
				found = true;
				previousMean = std::norm(previousZ - myZeros[j]);
				mean = std::norm(z - myZeros[j]);
				//Linear interpolation. Not totally smoothed
				//preciseAdvance = (eps - previousMean) / (mean - previousMean);
				//Logarithmic linear interpolation (boundaries: previous distance to root and actual dist,
				//find preciseAdvance corresponding to eps (reference) dist)
				preciseAdvance = (std::log(eps / previousMean)) / (std::log(mean / previousMean));
				//log log smoothing
				//preciseAdvance = std::log(-std::log(std::sqrt(std::norm(fDeZ))) / std::log(2));
				break;
			}
		}
		if (myPoles.size() != 0)
		{
			for (int j = 0; j < myPoles.size();j++)
			{
				if (std::norm(z - myZeros[j]) < eps)
				//if (std::abs((z.real() - myPoles[j].real())) < eps &&
				//	std::abs((z.imag() - myPoles[j].imag())) < eps)
				{
					indexColor = j;
					found = true;
					previousMean = std::norm(previousZ - myZeros[j]);
					mean = std::norm(z - myZeros[j]);
					preciseAdvance = (std::log(eps / previousMean)) / (std::log(mean / previousMean));
					//previousMean = (previousZ.real() - myZeros[j].real()) * (previousZ.real() - myZeros[j].real())
					//	+ (previousZ.imag() - myZeros[j].imag()) * (previousZ.imag() - myZeros[j].imag());
					//mean = (z.real() - myZeros[j].real()) * (z.real() - myZeros[j].real())
					//	+ (z.imag() - myZeros[j].imag()) * (z.imag() - myZeros[j].imag());
					//preciseAdvance = (mean - previousMean) / (eps*eps - previousMean);
					break;
				}
			}
		}

		if (found)
			break;
		iterations++;
		previousZ = z;
	}
	//System.out.println(Z.re+" "+Z.im);
	
	double preciseIter = iterations - 1 + preciseAdvance;
	//For log log smoothing
	//double preciseIter = iterations - preciseAdvance;
	//if(preciseAdvance < 0)
	//	std::cout << preciseAdvance << " " << previousMean << " " << mean << " " << preciseIter << std::endl;
	return rendu2(a, b, indexColor, iterations, preciseIter);
	double rouge = myColors[indexColor].r - iterations*(myColors[indexColor].r / myMaxIter);
	double vert = myColors[indexColor].g - iterations*(myColors[indexColor].g / myMaxIter);
	double bleu = myColors[indexColor].b - iterations*(myColors[indexColor].b / myMaxIter);

	return Color(rouge, vert, bleu);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Newton::complexD Newton::computeFDeZ(const complexD& Z, const std::vector<complexD>& roots)
{
	complexD FDeZ(Z - roots[0]);
	for (int j = 0; j < roots.size() - 1;j++)
		FDeZ = FDeZ * (Z - roots[j + 1]);   //(z-z1)(z-z2)...(z-zn) = f(z)
	return FDeZ;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
//Computes the derivative of a polynom from its roots, then deduces its value for Z
Newton::complexD Newton::derived(const complexD& Z, const std::vector<complexD>& roots)
{
	int aUn = 0;
	complexD FPrimeDeZ;
	for (int j = 0; j < roots.size();j++)
	{
		complexD product(1, 0);
		for (int k = 0; k < roots.size();k++)
		{
			//ZerosTemp[aUn].re=ZerosTemp[aUn].im=1;
			if (k != aUn)
				product = product * (Z - roots[k]);  //Product (ex u'vwx)
		}
		aUn++;
		FPrimeDeZ = FPrimeDeZ + (product);  //Sum the products to get the final derivative
	}
	return FPrimeDeZ;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Color Newton::rendu1(double a, double b, int indexColor, int iterations, double preciseIterations)
{
	double rouge = myColors[indexColor].r - preciseIterations*(myColors[indexColor].r / myMaxIter);
	double vert = myColors[indexColor].g - preciseIterations*(myColors[indexColor].g / myMaxIter);
	double bleu = myColors[indexColor].b - preciseIterations*(myColors[indexColor].b / myMaxIter);

	return Color(rouge, vert, bleu);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Color Newton::rendu2(double a, double b, int indexColor, int iterations, double preciseIterations)
{
	double theta = -std::abs(std::atan2(b, a));
	if(a > 0)
		theta = -std::abs(std::atan2(b, -a));
	double r = std::abs(std::sin(theta * preciseIterations / 32. + myColors[indexColor].r));
	double g = std::abs(std::sin(theta*preciseIterations / 55. +myColors[indexColor].g));
	double bb = std::abs(std::sin(theta*preciseIterations / 68. +myColors[indexColor].b));

	return Color(r, g, bb);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Color Newton::rendu3(double a, double b, int indexColor, int iterations, double preciseIterations)
{

//	int       r, g, b;
	double    R, G, B;
	double    k;

	/*R = 0.5+0.5*Math.sin(1.05*2.*Math.PI*iterations/30.);
	G = 0.5+0.5*Math.sin(1.11*2.*Math.PI*iterations/30.);
	B = 0.5+0.5*Math.sin(1.13*2.*Math.PI*iterations/30.);*/

	complexD z(a, b);
	//  pixel->V      = (float)(count-log2(-log(AbsComplex(&data->newton.root[k].K) * eps)));

	//double absDenominateur;
	//if (myPoles.size() == 0)
	//	absDenominateur = 1.0;
	//else
	//	absDenominateur = z.abs(FDeZP);
	//double abs = z.abs(FDeZ) > 0 ? z.abs(FDeZ) : 0.000000000000001;
	double atan = (double)std::atan2(z.imag(), z.real());
	//double truc = iterations - Math.log(-Math.log(abs*absDenominateur) / Math.log(2));
	//double truc = iterations -Math.log(-Math.log(z.abs(z)) / Math.log(2));
	//if (Math.log(abs*absDenominateur) >= 0)
	//	truc = iterations - Math.log(Math.log(abs*absDenominateur) / Math.log(2));
	//System.out.println(Math.log(-Math.log(abs*absDenominateur)));

	const double pi = 3.14159;

	R = 0.5 + 1.0*0.5*std::sin(atan + 2.*pi*preciseIterations / 11.0);
	G = 0.5 + 1.0*0.5*std::sin(atan + 2.*pi*preciseIterations / 13.0);
	B = 0.5 + 1.0*0.5*std::sin(atan + 2.*pi*preciseIterations / 17.0);

	k = 0.50;
	// System.out.println(R+" "+G+" "+B);
	R = (1. - k)*R + k*myColors[indexColor].r;
	G = (1. - k)*G + k*myColors[indexColor].g;
	B = (1. - k)*B + k*myColors[indexColor].b;

	/* double truc = 2*(z.abs(z))*Math.log((z.abs(z)))/Math.log(z.abs(derivee(z, zeros)));
	R = Math.abs(Math.sin( 2.*Math.PI*(double) r*truc/((double)iterations*300.0)));
	G = Math.abs(Math.sin( 2.*Math.PI*(double) g*truc/((double)iterations*300.0)));
	B = Math.abs(Math.sin( 2.*Math.PI*(double) b*truc/((double)iterations*300.0)));*/

	return Color(R, G, B);
}

FACTORY_REGISTER_TYPE(Newton, Fractal)