#include "Mandelbrot.h"

#include "ObjectFactoryManager.h"

#include "MandelJuliaBlackAndWhiteRenderer.h"
#include "MandelJuliaPredefRandomRenderer.h"
#include "MandelJuliaRandomRenderer2.h"
#include "MandelJuliaSineRenderer.h"

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <complex>
#define _USE_MATH_DEFINES
#include <math.h>

#include "exprtk.hpp"

#include <qcolor.h>


Mandelbrot::Mandelbrot(const Parameters& params)
:myIsLogLog(params.getBool("logLog", false))
,myMaxIt(params.getInt("maxIter", 100))
,myRefreshFrequency(10)
,XMIN(params.getDouble("xmin", -2.))
,XMAX(params.getDouble("xmax", 2.))
,YMIN(params.getDouble("ymin", -2.))
,YMAX(params.getDouble("ymax", 2.))
,myStrRenderer(params.getString("renderer", "Black & white"))
,myBailout(params.getDouble("bailout", 4))//12800000000000))
,myStripeDensity(params.getDouble("stripeDensity", 5))
,myComputationType((ComputeMandelbrot)params.getInt("computationType", TRIANGLE_INEQUALITY))
,myBrightnessFactor(params.getDouble("brightness", 1.))
,myIsLambertCorrection(params.getBool("lambertCorrection", true))
,myWidth(params.getInt("sizeX", 800))
,myHeight(params.getInt("sizeY", 800))
{
	initRenderer(myStrRenderer, params);
	//myComputationType = AVERAGE_CURVATURE_1;
	std::cout << myComputationType << std::endl;
	lua.open_libraries();

	// "bark" namespacing in Lua
	// namespacing is just putting things in a table
	//sol::table bark = lua.create_named_table("bark");
	lua.new_usertype<ComplexD>("Complex"
		, sol::constructors<ComplexD(), ComplexD(double, double)>()
		, "re", &ComplexD::re
		, "im", &ComplexD::im
		, "abs", &ComplexD::abs);
	lua["Complex"][sol::meta_function::addition] = (ComplexD (*)(const ComplexD&, const ComplexD&))&operator+;
	lua["Complex"][sol::meta_function::multiplication] = (ComplexD(*)(const ComplexD&, const ComplexD&))&operator*;
	lua["Complex"][sol::meta_function::to_string] = (std::ostream& (*)(std::ostream& o, const ComplexD& z)) &operator <<;
	lua["Complex"][sol::meta_function::power_of] = &ComplexD::pow;
	//	"g", &my_class::g); // the usual

	std::string s = "c = Complex.new(3, 4) "
		"d = Complex.new(4, 5) "
		"a = c + d "
		"print(a)";
	lua.script(s);

	//exprtk
	typedef exprtk::symbol_table<double> symbol_table_t;
	typedef exprtk::expression<double>     expression_t;
	typedef exprtk::parser<double>             parser_t;

	std::string expression_str = "x * x - y * y + a";
	std::string expression_str2 = "2 * x * y + b";

	// Register x with the symbol_table
	symbol_table_t symbol_table;
	symbol_table.add_variable("x", myx);
	symbol_table.add_variable("y", myy);
	symbol_table.add_variable("a", mya);
	symbol_table.add_variable("b", myb);

	// Instantiate expression and register symbol_table
	//expression_t expression;
	expression.register_symbol_table(symbol_table);

	// Instantiate parser and compile the expression
	parser_t parser;
	parser.compile(expression_str, expression);

	//expression_t expression2;
	expression2.register_symbol_table(symbol_table);
	parser_t parser2;
	parser2.compile(expression_str2, expression2);
	//

	//fparser
	fp.Parse("z^2 + c", "z,c");
	fp.Optimize();
}


Mandelbrot::~Mandelbrot()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Mandelbrot::initRenderer(const std::string& renderer, const Parameters& params)
{
	if (renderer == "Black & white")
	{
		myRenderer = std::make_unique<MandelJuliaBlackAndWhiteRenderer>(params);
	}
	else if (renderer == "Random")
	{
		myRenderer = std::make_unique<MandelJuliaPredefRandomRenderer>(params);
	}
	else if (renderer == "Random 2")
	{
		myRenderer = std::make_unique<MandelJuliaRandomRenderer2>(params);
	}
	else if (renderer == "Sine")
	{
		myRenderer = std::make_unique<MandelJuliaSineRenderer>(params);
	}
	else
	{
		ILogger::log() << "unknown renderer " << renderer << "\n";
	}
	

	//if (renderer == "Predefined")
	//{
	//	myFractalColor = params.getColor("fractalColor", Color());
	//	myIterationsColors.push_back(Color(1., 0., 0.));
	//	myIterationsColors.push_back(Color(1., 0.5, 0.));
	//	myIterationsColors.push_back(Color(1., 1., 0.));
	//	myIterationsColors.push_back(Color(0., 1., 0.));
	//	myIterationsColors.push_back(Color(0., 0., 1.));
	//		
	//}
	//else if (renderer == "Random")
	//{
	//	myFractalColor = params.getColor("fractalColor", Color());
	//	std::vector<boost::any> tmp = params.getVector("iterationColors", std::vector<boost::any>());
	//	for (auto elem : tmp) {
	//		myIterationsColors.push_back(boost::any_cast<Color>(elem));
	//	}
	//}
	//else if (renderer == "Sine")
	//{
	//	myFractalColor = params.getColor("fractalColor", Color());
	//	myIsMode3D = params.getBool("isMode3D", false);
	//	std::vector<boost::any> tmp = params.getVector("amplitudes", std::vector<boost::any>());
	//	for (auto elem : tmp)
	//		myAmplitudes.push_back(boost::any_cast<double>(elem));
	//	
	//	tmp = params.getVector("phases", std::vector<boost::any>());
	//	for (auto elem : tmp)
	//		myPhases.push_back(boost::any_cast<double>(elem));
	//	
	//	tmp = params.getVector("pulsations", std::vector<boost::any>());
	//	for (auto elem : tmp)
	//		myPulsations.push_back(boost::any_cast<double>(elem));

	//}
	//else if (renderer == "Black & white")
	//{
	//}
	//else
	//{
	//	ILogger::log() << "unknown renderer " << renderer << "\n";
	//}
}

//void Mandelbrot::computeFull(const Parameters& params)//, Array2D<Color>& out)
//{
//	Array2D<Color>& out = *myArray;
//
//	const double XMIN = params.getDouble("xmin", -2.);
//	const double XMAX = params.getDouble("xmax", 2.);
//	const double YMIN = params.getDouble("ymin", -2.);
//	const double YMAX = params.getDouble("ymax", 2.);
//	myIsLogLog = params.getBool("logLog", false);
//	myMaxIt = params.getInt("maxIter", 100);
//	int width = out.getWidth();
//	int height = out.getHeight();
//	
//	//for (int i = 0; i < 6;i++)          //On sauvegarde le tableau de couleurs de l'objet Infos
//	//	Couleurs[i] = Infos.getCouleur(i);
//
//	//BufferedImage image = new BufferedImage(largeur, hauteur, BufferedImage.TYPE_INT_ARGB);
//	////création de l’image au moyen de la classe BufferedImage
//	//WritableRaster raster = image.getRaster();
//	////appel de la méthode getRaster() afin d’obtenir un objet de type WritableRaster, vous    
//	////permettant d’accéder aux pixels de l’image et de les modifier.
//	//ColorModel model = image.getColorModel(); //renvoie le modèle de couleur de l’image       
//	//										  //mémorisée.
//
//	//this.maxIterations = Infos.getIterations();    //Sauvegarde du nombre max d'itérations
//	//fractalColor = Couleurs[5];                   //Couleur de l'Ensemble
//	//int argb = fractalColor.getRGB();             //Renvoie le code RGB de la couleur
//	//Object colorData = model.getDataElements(argb, null);
//	//this.typeRepresentation = Infos.getTypeRepresentation();
//	//System.out.println(Infos.getTypeRepresentation());
//
//	int cpt = 0;  //Un compteur, pour la barre de progression
//	int coeffRefresh = 0;
//
//	for (int i = 0; i < width; i++)		//boucle sur tous les pixels de l’image
//	{
//		for (int j = 0; j < height; j++)
//		{
//			//if (Stop.getStop())    //Si on a cliqué sur Stop
//			//{
//			//	i = largeur - 1;  //On passe aux derniers pixels de l'image, pour arrêter. On pourrait aussi faire un break
//			//	j = hauteur - 1;
//			//	/*On prévient l'utilisateur*/
//			//	JOptionPane.showMessageDialog(null,
//			//		"Interruption du calcul.", "Information",
//			//		JOptionPane.INFORMATION_MESSAGE);
//			//}
//
//			/*On calcule le point courant. Il est situé entre XMIN et XMAX (resp. YMIN et YMAX),
//			*  et il y a largeur points entre XMIN et XMAX (resp. longueur points entre YMIN etYMAX)*/
//			double a = XMIN + i * (XMAX - XMIN) / width;
//			double b = YMIN + j * (YMAX - YMIN) / height;
//			double preciseIter;
//			int iterations;
//			double x, y;
//			double xPrime, yPrime;
//			double sum;
//			if (!escapesToInfinity(a, b, iterations, preciseIter, x, y, xPrime, yPrime, sum, ParserById()))
//			{
//				//argb = fractalColor.getRGB();   //Affecte le code RGB à un entier (compris entre 0 et 256^3)
//
//				out(i, j) = Color(1., 0., 0.);
//			}
//
//			else  //Si ça ne diverge pas
//			{
//				//if (typeRepresentation == "Dégradé de gris") //On regarde le mode de représentation graphique choisi -Gris ici-
//				{
//					double coeff = 255 / myMaxIt;    //On calcule le coefficient, pour la couleur
//					int rgb;
//
//					if (!myIsLogLog)
//						rgb = (int)(iterations*coeff);
//					else  //Adoucissement log-log
//					{
//						double fin = preciseIter - iterations;
//						double coeff2 = fin *coeff;
//						rgb = (int)((iterations*coeff) + coeff2);
//						rgb = rgb > 255 ? 255 : rgb;
//					}
//
//					/*On détermine la couleur pour le point en cours de calcul,
//					dépendante du nombre d'itérations*/
//					Color fractal = Color(rgb / 255.);
//
//					out(i, j) = fractal;
//
//					//argb = fractal.getRGB();    //On récupère le code RGB de la couleur
//					//colorData = model.getDataElements(argb, null);
//					//raster.setDataElements(i, j, colorData);
//				}
//			}
//			int perc = (int)(((double)cpt / (width * height)) * 100);
//			if (perc > myRefreshFrequency * coeffRefresh)
//			{
//				dispatchComputationAdvances(perc);
//				coeffRefresh++;
//			}
//			cpt++;
//		}
//	}
//}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Color Mandelbrot::computePixel(double a, double b, const Parameters& params, ParserById& parserById)//, Array2D<Color>& out)//std::vector<FunctionParser_cd>& parsers
{
	myIsLogLog = params.getBool("logLog", false);
	myMaxIt = params.getInt("maxIter", 100);

	double preciseIter;
	int iterations;
	double x, y;
	double xPrime, yPrime;
	double sum = 0;
	double value = 0;

	escapesToInfinity(a, b, iterations, preciseIter, x, y, xPrime, yPrime, sum, parserById);
	double r = (double)(0.5 * std::sin(0.2 * sum + 0));
	double g = (double)(0.5 * std::sin(0.3  * sum + 0.));
	double bl = (double)(0.5 * std::sin(0.4 * sum + 0.));

	r = 1 * sum + 0. * (1 - sum);
	g = 0 * sum + 1. * (1 - sum);
	bl = 0 * sum + 0. * (1 - sum);
	//std::cout << sum << std::endl;

	//r = (1. - 1. * sum);
	//g = r;
	//bl = r;

	

	if(myIsLambertCorrection)
		return compute3D(a, b, x, y, xPrime, yPrime, iterations, preciseIter, sum, parserById) * myBrightnessFactor;
	else {
		value = myComputationType & (BRANCHING | FOLD) ? sum : preciseIter / myMaxIt ;
		return myRenderer->computeColor(iterations, value, x, y, xPrime, yPrime) * myBrightnessFactor;
	}
	//
	//double saveX = x;
	//double saveY = y;
	//double saveA = a;
	//double saveB = b;
	//double saveSum = sum;

	//value = myComputationType & BRANCHING ? preciseIter / myMaxIt : sum;

	//Eigen::Vector3d p1(a, b, sum);//std::log(std::sqrt(x*x + y*y));// / (std::pow(myBailout, 12));
	//Color col1 = myRenderer->computeColor(iterations, value, x, y, xPrime, yPrime);
	//int width = 800, height = 800;
	//double px = (a - XMIN) * width / (XMAX - XMIN);
	//double py = (b - YMIN) * height / (YMAX - YMIN);

	//a = XMIN + (px + 0.3) * (XMAX - XMIN) / width;
	//b = YMIN + (py) * (YMAX - YMIN) / height;

	//escapesToInfinity(a, b, iterations, preciseIter, x, y, xPrime, yPrime, sum);
	//Eigen::Vector3d p2(a, b, sum);//std::log(std::sqrt(x*x + y*y));// / (std::pow(myBailout, 12));
	//value = myComputationType & BRANCHING ? preciseIter / myMaxIt : sum;
	//Color col2 = myRenderer->computeColor(iterations, value, x, y, xPrime, yPrime);

	//a = XMIN + (px) * (XMAX - XMIN) / width;
	//b = YMIN + (py + 0.3) * (YMAX - YMIN) / height;
	//escapesToInfinity(a, b, iterations, preciseIter, x, y, xPrime, yPrime, sum);
	//value = myComputationType & BRANCHING ? preciseIter / myMaxIt : sum;
	//Eigen::Vector3d p3(a, b, sum);//std::log(std::sqrt(x*x + y*y));// / (std::pow(myBailout, 12));
	//Color col3 = myRenderer->computeColor(iterations, value, x, y, xPrime, yPrime);

	//double centerX = (XMAX + XMIN) / 2.;
	//double centerY = (YMAX + YMIN) / 2.;
	//double lightZ = 100. * std::max(p1.z(), std::max(p2.z(), p3.z()));

	//Eigen::Vector3d u = p2 - p1;
	//u.normalize();

	//Eigen::Vector3d v = p3 - p1;
	//v.normalize();
	////std::cout << x << " " << y << " " << ux << " " << uy << " " << uz << " " << vx << " " << vy << " " << vz << std::endl;

	//a = saveA;
	//b = saveB;
	//x = saveX;
	//y = saveY;

	//Eigen::Vector3d n = u.cross(v);
	//n.normalize();

	//Eigen::Vector3d lightVecX(centerX - a, centerY - b, lightZ - p1.z());
	//lightVecX.normalize();

	//double lightIntensity = 1;//00. / (norm * norm);
	//double ambientLight = 0.5;
	//double dot = lightVecX.dot(n);//*nx + lightVecY * ny + lightVecZ * nz;
	////dot = dot < 0 ? 0 : dot;
	////std::cout << dot << std::endl;
	////preciseIter = saveSum;
	//value = myComputationType & BRANCHING ? saveSum : preciseIter / myMaxIt;
	////std::cout << nx << " " << ny << " " << nz << " " << dot << std::endl;

	//Color finalCol = (col1 + col2 + col3) / 3.;

	//QColor qcol(finalCol.r * 255, finalCol.g * 255, finalCol.b * 255);
	//qcol.toHsv();
	//qreal h, s, vp;
	//qcol.getHsvF(&h, &s, &vp);
	//vp *= lightIntensity * std::abs(dot);
	//qcol.setHsvF(h, s, vp);
	////return Color(qcol.redF(), qcol.greenF(), qcol.blueF());
	////return Color(r, g, bl);
	////return (col1 + col2 + col3) / 3. * (((lightIntensity - ambientLight) * dot + lightIntensity) * dot + ambientLight); //* lightIntensity * std::abs(dot);
	//return myRenderer->computeColor(iterations, value, x, y, xPrime, yPrime);//*lightIntensity * std::abs(dot);

	//if (!escapesToInfinity(a, b, iterations, preciseIter, x, y, xPrime, yPrime))
	//{
	//	return myFractalColor;
	//}
	//else  //Si ça ne diverge pas
	//{
	//	return myRenderer->computeColor(iterations, preciseIter, x, y, xPrime, yPrime);

	//	//if (myRenderer == "Black and white")
	//	//	return blackAndWhiteRenderer(iterations, preciseIter);
	//	//else if (myRenderer == "Predefined")
	//	//	return predefinedAndRandomRenderer(iterations, preciseIter);
	//	//else if (myRenderer == "Random")
	//	//	return predefinedAndRandomRenderer(iterations, preciseIter);
	//	//else if (myRenderer == "Sine")
	//	//	return sineRenderer(iterations, preciseIter, false);

	//	//if (typeRepresentation == "Dégradé de gris") //On regarde le mode de représentation graphique choisi -Gris ici-
	//	{
	//		double coeff = 255 / myMaxIt;    //On calcule le coefficient, pour la couleur
	//		int rgb;

	//		if (!myIsLogLog)
	//			rgb = (int)(iterations*coeff);
	//		else  //Adoucissement log-log
	//		{
	//			double fin = preciseIter - iterations;
	//			double coeff2 = fin *coeff;
	//			rgb = (int)((iterations*coeff) + coeff2);
	//			rgb = rgb > 255 ? 255 : rgb;
	//		}

	//		/*On détermine la couleur pour le point en cours de calcul,
	//		dépendante du nombre d'itérations*/
	//		return Color(rgb / 255.);
	//	}
	//}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool Mandelbrot::escapesToInfinity(double a, double b, int& iterations, double& preciseIter, double& x, double& y, double& xPrime, double& yPrime, double& value, ParserById& parserById)
{
	x = 0.0;
	y = 0.0;
	xPrime = 0;
	yPrime = 0;
	//   int iterations = 0;
	iterations = 0;  //On fixe le nombre d'itérations à 0
	double sum = 0;
	double prevSum = 0;
	ComplexD znpprev;
	ComplexD znprev;
	int iterationsBranching = 0;
	int skipLastIterBranching = 0;
	double fold = 0;
	//ComplexD point(a, b);
	//ComplexD z(x, y);
	//lua["point"] = point;
	//lua["z"] = z;
	//lua


	//exprtk

	//fparser
	std::complex<double> base(a, b);
	//ComplexD base(a, b);



	do
	{
		iterations++;
		if (iterations == myMaxIt) return false;

		double xnew, ynew;
		auto parser = parserById.find(Mandelbrot::FUNCTION);
		if (parser != parserById.end())
		{
			std::complex<double> variables[4]{ std::complex<double>(x, y), std::complex<double>(), std::complex<double>(), base };
			std::complex<double> z = parser->second.eval(variables);
			xnew = z.real();
			ynew = z.imag();
		}
		else
		{
			xnew = x * x - y * y + a;
			ynew = 2 * x * y + b;
		}
		//double xnew = x * x - y * y + a;
		//double ynew = 2 * x * y + b;

		//exprtk
		//myx = x;
		//myy = y;
		//mya = a;
		//myb = b;
		//double xnew = expression.value();
		//double ynew = expression2.value();
		//

		//lua
		//std::string s = "z = z^2 + point";
		//lua.script(s);
		//z = lua["z"];
		//double xnew = z.re;
		//double ynew = z.im;
		//

		//fparser
		////std::complex<double> variables[2] = {std::complex<double>(x, y), base};
		//ComplexD variables[2] = { ComplexD(x, y), base };
		////std::complex<double> result = fp.Eval(variables);
		//ComplexD result = fp.Eval(variables);
		//double xnew = result.re;
		//double ynew = result.im;
		//

		double _xPrime = 2.*(x*xPrime - y*yPrime) + 1.;
		double _yPrime = 2.*(x*yPrime + y*xPrime);

		if (myComputationType & (BRANCHING | FOLD))
			computeBranching(iterations, x, y, xnew, ynew, a, b, prevSum, sum, skipLastIterBranching, znpprev, znprev, parserById);
		//fold = std::exp(-ComplexD(xnew, ynew).abs() - 0.5 / ((ComplexD(x, y) - ComplexD(xnew, ynew)).abs())) + fold;
		//fold = 1. / (ComplexD(xnew, ynew).abs() + 1) + fold;
		//
		//Eigen::Vector2d v(xnew, ynew);
		//fold = 1. / (std::abs(v.norm() - 2.)+0.01) + fold;
		//
		Eigen::Vector2d p1(1, 1), p2(0, 0);
		double m = (p1.y() - p2.y()) / (p1.x() - p2.x());
		double p = p1.y() - m * p1.x();
		double dist = std::abs(ynew - m * xnew + p) / std::sqrt(1 + m * m);
		//fold = 1. / (dist + 0.0001) + fold;
		//
		ComplexD znew(xnew, ynew);
		double at = std::atan2(znew.im, znew.re);
		//if (at < 0)
		//	at = (at + 2 * M_PI);
		//at /= 2. * M_PI;
		fold = std::cos(12*at) / znew.abs() + fold;

		//branching via triangle inequality
		//if (iterationsBranching >= 2)
		//{
		//	std::complex<double> znPrev(x * x - y * y, 2 * x * y);//znPrev *= znPrev;
		//	std::complex<double> zn(xnew, ynew);
		//	std::complex<double> constant(a, b);
		//	double lowerBound = std::abs(std::abs(znPrev) - std::abs(constant));
		//	double upperBound = std::abs(znPrev) + std::abs(constant);
		//	double addEnd = (std::abs(zn) - lowerBound) / (upperBound - lowerBound);
		//	prevSum = sum;
		//	sum += addEnd;//0.5 * std::sin(std::atan2(y, x)) + 0.5;//
		//	//std::cout << addEnd << std::endl;
		//}

		//branching via average curvature
		//if (iterations == 1) {
		//	znpprev = Complex<double>(xnew, ynew);
		//}
		//if (iterations == 2) {
		//	
		//	znprev = Complex<double>(xnew, ynew);
		//}
		//if (iterations >= 3)
		//{
		//	Complex<double> zn(xnew, ynew);
		//	if (znprev != znpprev)
		//	{
		//		Complex<double> tmpZ = (zn - znprev) / (znprev - znpprev);
		//		//double addEnd = std::abs(std::atan2(tmpZ.im, tmpZ.re));//std::abs(2 * std::atan2(tmpZ.imag(), tmpZ.real() + std::abs(tmpZ)));
		//		//addEnd /= M_PI;
		//		double addEnd = std::atan2(tmpZ.im, tmpZ.re);
		//		if (addEnd < 0)
		//			addEnd = (addEnd + 2 * M_PI);
		//		addEnd = (std::cos(addEnd) + 1.) / 2.;
		//		//addEnd /= 2 * M_PI;

		//		prevSum = sum;
		//		sum += addEnd;
		//		znpprev = znprev;
		//		znprev = zn;
		//	}
		//	else
		//		skipLastIterBranching++;
		//}
		

		//branching via stripe average coloring
		//if (iterations >= 1)
		//{
		//	prevSum = sum;
		//	sum += 0.5 * std::sin(myStripeDensity * std::atan2(y, x)) + 0.5;//
		//}

		x = xnew;
		y = ynew;
		xPrime = _xPrime;
		yPrime = _yPrime;
		
	} while (x*x + y*y <= myBailout);//x <= 2 && y <= 2);

	if (myComputationType & BRANCHING)
		normalizeBranching(iterations, skipLastIterBranching, sum, prevSum);
	//for (int i = 0; i < 3; i++)
	//{
	//	double xnew = x * x - y * y + a;
	//	double ynew = 2 * x * y + b;

	//	double _xPrime = 2.*(x*xPrime - y*yPrime) + 1.;
	//	double _yPrime = 2.*(x*yPrime + y*xPrime);

	//	prevSum = sum;
	//	sum += 0.5 * std::sin(std::atan2(y, x)) + 0.5;//addEnd;

	//	x = xnew;
	//	y = ynew;
	//	xPrime = _xPrime;
	//	yPrime = _yPrime;
	//}

	//branching via triangle inequality
	//if (iterations >= 2) {
	//	sum /= (iterations);
	//	prevSum /= (iterations - 1); 
	//}

	//branching via average curvature
	//if (iterations >= 4) {
	//	prevSum /= (iterations - 3 - skipLastIterBranching);
	//}
	//if (iterations >= 3) {
	//	sum /= (iterations - 2 - skipLastIterBranching);
	//}

	//branching via stripe average coloring
	//if (iterations >= 1) {
	//	sum /= (iterations + 1);
	//	prevSum /= (iterations);
	//}

	//sum = ((sum)) + 1 - std::log(std::log((std::sqrt(x*x + y*y)))) / std::log(myBailout);
	//float frac = 1.0 + (log2(log(myBailout) / log(x*x + y*y)));
	//std::cout << sum << std::endl;

	if (iterations < myMaxIt)
	{
		if (myIsLogLog) {
			preciseIter = iterations + 1 - std::log(std::log(std::sqrt(x*x + y*y))) / std::log(2);

			double advance = preciseIter - (int)preciseIter;

			double il = 1.0 / std::log(2);
			double lp = log(log(myBailout) / 2.);
			double f = il*lp - il*log(std::abs(log(std::sqrt(x*x + y*y))));
			sum = prevSum + (sum - prevSum)*(f + 1.0);
			//average curvature
			//if(sum < 0)
			//	sum = (sum + 2 * M_PI);
			//sum /= 2 * M_PI;
			//sum = frac * sum + (1 - frac) * prevSum;
		}
		else
		{
			for (int k = 0; k < 3; k++)
			{
				// P(z)^2 + Z
				double xnew = x*x - y*y + a;
				double ynew = 2.*x*y + b;
				// 2.P'(Z).P(Z) + 1
				double _xPrime = 2.*(x*xPrime - y*yPrime) + 1.;
				double _yPrime = 2.*(x*yPrime + y*xPrime);

				x = xnew;
				y = ynew;
				xPrime = _xPrime;
				yPrime = _yPrime;
			}
			double reDiv = x*xPrime + y*yPrime;
			double imDiv = x*yPrime - y*xPrime;

			mode3D = (double)std::atan2(imDiv, reDiv);

			preciseIter = -(float)(std::log(0.5* std::log(x*x + y*y) / std::log(2)) / std::log(2) - iterations - 3);
		}
	}
	//
	value = myComputationType & ADDEND ? sum : preciseIter;

	auto parser = parserById.find(Mandelbrot::VALUE_RERANGE);
	if (parser != parserById.end())
	{
		std::complex<double> variables[1]{ std::complex<double>(value, 0.)};
		std::complex<double> z = parser->second.eval(variables);
		value = z.real();
	}
	else
	{
		value = std::log(std::abs(value) + 1);
	}
	return true;
}

void Mandelbrot::computeBranching(int iterations, double x, double y, double xnew, double ynew, double a, double b,
	double& prevSum, double& sum, int& skipLastIterBranching, ComplexD& znpprev, ComplexD& znprev, std::map<int, MathParser>& parserById)
{
	auto parser = parserById.find(Mandelbrot::ADDEND_FUNCTION);
	if (parser != parserById.end())
	{
		////branching via average curvature
		//if (iterations == 1) {
		//	znpprev = ComplexD(xnew, ynew);
		//}
		//if (iterations == 2) {

		//	znprev = ComplexD(xnew, ynew);
		//}
		

			std::complex<double> variables[5]{
				std::complex<double>(xnew, ynew), std::complex<double>(znprev.re, znprev.im), std::complex<double>(znpprev.re, znpprev.im), std::complex<double>(a, b), std::complex<double>(sum, 0) };
			prevSum = sum;
			sum = parser->second.eval(variables).real();
			if (std::isnan(sum) || std::isinf(sum))
			{
				std::cout << "nan sum" << std::endl;
				sum = prevSum;
			}
			znpprev = znprev;
			znprev = ComplexD(xnew, ynew);
		//if (iterations >= 3)
		//{
		//	znpprev = znprev;
		//	znprev = ComplexD(xnew, ynew);
		//}
		//}
	}
	else
	{
		switch (myComputationType & BRANCHING)
		{
		case TRIANGLE_INEQUALITY:
		{
			if (iterations >= 2)
			{
				znprev = ComplexD(x * x - y * y, 2 * x * y);//znPrev *= znPrev;
				ComplexD zn(xnew, ynew);
				ComplexD constant(a, b);
				double lowerBound = std::abs(znprev.abs() - constant.abs());
				double upperBound = znprev.abs() + constant.abs();
				if (upperBound != lowerBound)
				{
					double addEnd = (zn.abs() - lowerBound) / (upperBound - lowerBound);
					prevSum = sum;
					sum += addEnd;//0.5 * std::sin(std::atan2(y, x)) + 0.5;//
					//std::cout << addEnd << std::endl;
				}
				else
					skipLastIterBranching++;
			}
		}
		break;

		case AVERAGE_CURVATURE_1:
		case AVERAGE_CURVATURE_2:
		case AVERAGE_CURVATURE_3:
		{
			//branching via average curvature
			if (iterations == 1) {
				znpprev = ComplexD(xnew, ynew);
			}
			if (iterations == 2) {

				znprev = ComplexD(xnew, ynew);
			}
			if (iterations >= 3)
			{
				ComplexD zn(xnew, ynew);
				if (znprev != znpprev)
				{
					ComplexD tmpZ = (zn - znprev) / (znprev - znpprev);
					double addEnd = 0;
					if ((myComputationType & AVERAGE_CURVATURE_1) == AVERAGE_CURVATURE_1)
					{
						addEnd = std::abs(std::atan2(tmpZ.im, tmpZ.re));//std::abs(2 * std::atan2(tmpZ.imag(), tmpZ.real() + std::abs(tmpZ)));
						addEnd /= M_PI;
					}
					else if ((myComputationType & AVERAGE_CURVATURE_2) == AVERAGE_CURVATURE_2)
					{
						addEnd = std::atan2(tmpZ.im, tmpZ.re);
						if (addEnd < 0)
							addEnd = (addEnd + 2 * M_PI);
						addEnd = (std::cos(addEnd) + 1.) / 2.;
					}
					else
					{
						addEnd = std::atan2(tmpZ.im, tmpZ.re);
						if (addEnd < 0)
							addEnd = (addEnd + 2 * M_PI);
						addEnd /= 2 * M_PI;
					}


					prevSum = sum;
					sum += addEnd;

				}
				else
					skipLastIterBranching++;

				znpprev = znprev;
				znprev = zn;
			}
		}
		break;

		case STRIPE_AVERAGE:
		{
			//branching via stripe average coloring
			if (iterations >= 1)
			{
				prevSum = sum;
				sum += 0.5 * std::sin(myStripeDensity * std::atan2(y, x)) + 0.5;//
			}
		}
		break;
		}

		switch (myComputationType & FOLD)
		{
		case FOLD_LINE:
		{
			prevSum = sum;
			Eigen::Vector2d p1(1, 1), p2(0, 0);
			double m = (p1.y() - p2.y()) / (p1.x() - p2.x());
			double p = p1.y() - m * p1.x();
			double dist = std::abs(ynew - m * xnew + p) / std::sqrt(1 + m * m);
			double fold = 1. / (dist + 0.0001) + sum;
			sum = fold;
		}
		break;
		case FOLD_CIRCLE:
		{
			//fold = std::exp(-ComplexD(xnew, ynew).abs() - 0.5 / ((ComplexD(x, y) - ComplexD(xnew, ynew)).abs())) + fold;
					//fold = 1. / (ComplexD(xnew, ynew).abs() + 1) + fold;
					//
			prevSum = sum;
			Eigen::Vector2d v(xnew, ynew);
			double fold = 1. / (std::abs(v.norm() - 2.) + 0.01) + sum;
			sum = fold;

			//
			//ComplexD znew(xnew, ynew);
			//double at = std::atan2(znew.im, znew.re);
			////if (at < 0)
			////	at = (at + 2 * M_PI);
			////at /= 2. * M_PI;
			//fold = std::cos(12 * at) / znew.abs() + fold;
			//sum = fold;
		}
		break;
		case FOLD_SQUARE:
		{
			//fold += znew / zprev
			//fold = cos(fold);
			//(-2, -1) (1, 2)
			Eigen::Vector2d lu(-2, -1);
			Eigen::Vector2d rb(1, 2);
			Eigen::Vector2d ru(rb.x(), lu.y());
			Eigen::Vector2d lb(lu.x(), rb.y());

			//haut
			Eigen::Vector2d edge(ru - lu);
			Eigen::Vector2d ap(xnew - lu.x(), ynew - lu.y());
			double t = edge.dot(ap) / edge.squaredNorm();
			if (t < 0 || t > 1)
				t = std::min(std::max(0., t), 1.);
			Eigen::Vector2d pPrime = lu + edge * t;//
			double dist = Eigen::Vector2d(pPrime.x() - xnew, pPrime.y() - ynew).norm();

			//droite
			edge = Eigen::Vector2d(rb - ru);
			ap = Eigen::Vector2d(xnew - ru.x(), ynew - ru.y());
			t = edge.dot(ap) / edge.squaredNorm();
			if (t < 0 || t > 1)
				t = std::min(std::max(0., t), 1.);
			pPrime = ru + edge * t;//
			dist = std::min(dist, Eigen::Vector2d(pPrime.x() - xnew, pPrime.y() - ynew).norm());

			//bas
			edge = Eigen::Vector2d(lb - rb);
			ap = Eigen::Vector2d(xnew - rb.x(), ynew - rb.y());
			t = edge.dot(ap) / edge.squaredNorm();
			if (t < 0 || t > 1)
				t = std::min(std::max(0., t), 1.);
			pPrime = rb + edge * t;//
			dist = std::min(dist, Eigen::Vector2d(pPrime.x() - xnew, pPrime.y() - ynew).norm());

			//gauche
			edge = Eigen::Vector2d(lu - lb);
			ap = Eigen::Vector2d(xnew - lb.x(), ynew - lb.y());
			t = edge.dot(ap) / edge.squaredNorm();
			if (t < 0 || t > 1)
				t = std::min(std::max(0., t), 1.);
			pPrime = lb + edge * t;//
			dist = std::min(dist, Eigen::Vector2d(pPrime.x() - xnew, pPrime.y() - ynew).norm());

			prevSum = sum;
			double fold = 1. / (dist + 0.0001) + sum;
			sum = fold;
		}
		break;

		case FOLD_EXP_SMOOTHING:
		{
			prevSum = sum;
			double fold = std::exp(-ComplexD(xnew, ynew).abs() - 0.5 / ((ComplexD(x, y) - ComplexD(xnew, ynew)).abs())) + sum;
			sum = fold;
		}
		break;

		case FOLD_Z_SMOOTHING:
		{
			prevSum = sum;
			double fold = 1. / (ComplexD(xnew, ynew).abs() + 1) + sum;
			sum = fold;
		}
		break;
		}
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Mandelbrot::normalizeBranching(int iterations, int skipLastIterBranching, double& sum, double& prevSum)
{
	switch (myComputationType & BRANCHING)
	{
	case TRIANGLE_INEQUALITY:
	{
		//branching via triangle inequality
		if (iterations >= 2) {
			sum /= (iterations);
			prevSum /= (iterations - 1);
		}
	}
	break;

	case AVERAGE_CURVATURE_1:
	case AVERAGE_CURVATURE_2:
	case AVERAGE_CURVATURE_3:
	{
		//branching via average curvature
		if (iterations >= 4) {
			prevSum /= (iterations - 3 - skipLastIterBranching);
		}
		if (iterations >= 3) {
			sum /= (iterations - 2 - skipLastIterBranching);
		}
	}
	break;

	case STRIPE_AVERAGE:
	{
		//branching via stripe average coloring
		if (iterations >= 1) {
			sum /= (iterations + 1);
			prevSum /= (iterations);
		}
	}
	break;
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Color Mandelbrot::compute3D(double a, double b, double x, double y, double xPrime, double yPrime, int iterations, double preciseIter, double addEndMeanSum, ParserById& parserById)
{
	double saveX = x;
	double saveY = y;
	double saveA = a;
	double saveB = b;
	double saveSum = addEndMeanSum;

	double value = myComputationType & ADDEND ? addEndMeanSum:preciseIter / myMaxIt;

	Eigen::Vector3d p1(a, b, rerange3DHeight(value, parserById));//std::log(std::sqrt(x*x + y*y));// / (std::pow(myBailout, 12));
	Color col1 = myRenderer->computeColor(iterations, value, x, y, xPrime, yPrime);
	double px = (a - XMIN) * myWidth / (XMAX - XMIN);
	double py = (b - YMIN) * myHeight / (YMAX - YMIN);

	a = XMIN + (px + 1.) * (XMAX - XMIN) / myWidth;
	b = YMIN + (py + 0.5) * (YMAX - YMIN) / myHeight;

	escapesToInfinity(a, b, iterations, preciseIter, x, y, xPrime, yPrime, addEndMeanSum, parserById);
	value = myComputationType & ADDEND ? addEndMeanSum : preciseIter / myMaxIt;
	Eigen::Vector3d p2(a, b, rerange3DHeight(value, parserById));//std::log(std::sqrt(x*x + y*y));// / (std::pow(myBailout, 12));
	
	Color col2 = myRenderer->computeColor(iterations, value, x, y, xPrime, yPrime);

	a = XMIN + (px + 0.5) * (XMAX - XMIN) / myWidth;
	b = YMIN + (py + 1.) * (YMAX - YMIN) / myHeight;
	escapesToInfinity(a, b, iterations, preciseIter, x, y, xPrime, yPrime, addEndMeanSum, parserById);
	value = myComputationType & ADDEND ? addEndMeanSum : preciseIter / myMaxIt;
	Eigen::Vector3d p3(a, b, rerange3DHeight(value, parserById));//std::log(std::sqrt(x*x + y*y));// / (std::pow(myBailout, 12));
	Color col3 = myRenderer->computeColor(iterations, value, x, y, xPrime, yPrime);

	double centerX = -0.667;//(XMAX + XMIN) / 2.;
	double centerY = -0.667;//(YMAX + YMIN) / 2.;
	double lightZ = 100. * std::max(p1.z(), std::max(p2.z(), p3.z()));

	Eigen::Vector3d u = p2 - p1;
	u.normalize();

	Eigen::Vector3d v = p3 - p1;
	v.normalize();
	//std::cout << x << " " << y << " " << ux << " " << uy << " " << uz << " " << vx << " " << vy << " " << vz << std::endl;

	a = saveA;
	b = saveB;
	x = saveX;
	y = saveY;

	Eigen::Vector3d n = u.cross(v);
	n.normalize();

	Eigen::Vector3d lightVecX(-0.6, -0.6, 0.5);//centerX - a, centerY - b, lightZ - p1.z());
	lightVecX.normalize();

	double lightIntensity = 0.5;//00. / (norm * norm);
	double ambientLight = 0.5;
	double dot = lightVecX.dot(n);//*nx + lightVecY * ny + lightVecZ * nz;
								  //dot = dot < 0 ? 0 : dot;
								  //std::cout << dot << std::endl;
								  //preciseIter = saveSum;
	value = myComputationType & BRANCHING ? saveSum : preciseIter / myMaxIt;
	//std::cout << nx << " " << ny << " " << nz << " " << dot << std::endl;

	Color finalCol = (col1 + col2 + col3) / 3.;

	QColor qcol(finalCol.r * 255, finalCol.g * 255, finalCol.b * 255);
	qcol.toHsv();
	qreal h, s, vp;
	qcol.getHsvF(&h, &s, &vp);
	vp *= lightIntensity * std::abs(dot);
	qcol.setHsvF(h, s, vp);
	//return Color(qcol.redF(), qcol.greenF(), qcol.blueF());
	//return Color(r, g, bl);
	//V moi
	Eigen::Vector3d reflected = (2 * dot * n - lightVecX).normalized();
	Eigen::Vector3d viewer = Eigen::Vector3d{ 0., 0., 1. };//centerX - a, centerY - b, 10}.normalized();
	//dot = dot < 0 ? 0 : dot;
	int alpha = 8;
	//return col1 * (lightIntensity * dot + ambientLight + std::pow(reflected.dot(viewer), alpha));//(((lightIntensity - ambientLight) * dot + lightIntensity) * dot + ambientLight);
	//V autre
	return finalCol * (((lightIntensity - ambientLight) * dot + lightIntensity) * dot + ambientLight) +std::pow(reflected.dot(viewer), alpha);
	return (col1 + col2 + col3) / 3. * (((lightIntensity - ambientLight) * dot + lightIntensity) * dot + ambientLight); //* lightIntensity * std::abs(dot);
	//return myRenderer->computeColor(iterations, value, x, y, xPrime, yPrime);//*lightIntensity * std::abs(dot);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
double Mandelbrot::rerange3DHeight(double value, ParserById& parserById)
{
	auto parser = parserById.find(Mandelbrot::RERANGE_3D_HEIGHT);
	if (parser != parserById.end())
	{
		std::complex<double> variables[1]{
			std::complex<double>(value, 0)};

		return parser->second.eval(variables).real();
	}

	return value;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Color Mandelbrot::predefinedAndRandomRenderer(int iterations, double preciseIter)
{
	/*Il nous faut réaliser un dégradé de couleurs...On a défini 5 couleurs
	* utilisées en fonction du nombre d'itérations. Chaque couleur doit tendre
	* vers celle qui la suit et celle qui la précède*/
	Color fractal;  //On crée une couleur pour le point en cours
	Color CouleurDAvant;   //On définit une couleur qui précède
	Color CouleurDApres;   //On définit une couleur qui suit
									   /*On définit un pas...4 couleurs, soit une toutes les (maxIterations / 4)*/
	double step = (double) myMaxIt / 4;
	/*On définit 3 coefficients, un par couleur*/
	double coeffR = 0;
	double coeffG = 0;
	double coeffB = 0;
	double red = 0., green = 0., blue = 0.;  //On définit 3 composantes R,G,B
	int variable = 0;
	int range = 10;

	/* Pour les "pas" premières itérations, on cherche à passer de la couleur[0] à couleur[1]*/
	if (iterations <= step)
	{
		range = (int)step;
		variable = iterations;
		CouleurDAvant = myIterationsColors[0];   //Donc on les définit telles quelles
		CouleurDApres = myIterationsColors[1];
	}
	else if (iterations > step && iterations <= 2 * step)   //Idem, couleur 1 -> 2
	{
		range = (int)(2 * step - step);
		variable = (int)(iterations - (step + 1));
		CouleurDAvant = myIterationsColors[1];
		CouleurDApres = myIterationsColors[2];
	}
	else if (iterations > 2 * step && iterations <= 3 * step)  //Idem, couleur 2 -> 3
	{
		range = (int)(3 * step - 2 * step);
		variable = (int)(iterations - (2 * step + 1));
		CouleurDAvant = myIterationsColors[2];
		CouleurDApres = myIterationsColors[3];
	}
	else if (iterations > 3 * step && iterations <= myMaxIt)  //Idem, couleur 3 -> 4
	{
		range = (int)(myMaxIt - 1 - 3 * step);
		variable = (int)(iterations - (3 * step + 1));
		CouleurDAvant = myIterationsColors[3];
		CouleurDApres = myIterationsColors[4];
	}

	/*On initialise nos coefficients, en faisant la différence des 2 composantes des 2 couleurs,
	* normalisés par un rapport pas.*/
	coeffR = (CouleurDApres.r - CouleurDAvant.r) / (double)range;
	coeffG = (CouleurDApres.g - CouleurDAvant.g) / (double)range;
	coeffB = (CouleurDApres.b - CouleurDAvant.b) / (double)range;

	//variable = (iterations%(int)pas); if (variable==0) variable = (int)pas;
	/*On crée les composantes rgb du point, en prenant la composante d'avant, à
	* laquelle on ajoute le coefficient multiplié par le pas (en gros)*/
	red = (CouleurDAvant.r + ((variable)) * coeffR);
	green = (CouleurDAvant.g + ((variable)) * coeffG);
	blue = (CouleurDAvant.b + ((variable)) * coeffB);

	if (myIsLogLog) 
	{
		double fin = preciseIter - iterations;

		coeffR = coeffR * fin;
		coeffG = coeffG * fin;
		coeffB = coeffB * fin;
	}

	fractal = Color(red + coeffR, green + coeffG, blue + coeffB);  

	return fractal;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Color Mandelbrot::blackAndWhiteRenderer(int iterations, double preciseIter)
{
	double coeff = 255 / myMaxIt;    
	int rgb;

	if (!myIsLogLog)
		rgb = (int)(iterations*coeff);
	else 
	{
		double fin = preciseIter - iterations;
		double coeff2 = fin *coeff;
		rgb = (int)((iterations*coeff) + coeff2);
		rgb = rgb > 255 ? 255 : rgb;
	}

	return Color(rgb / 255.);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Color Mandelbrot::sineRenderer(int iterations, double preciseIter, bool is3Dmode)
{
	Color fractal;
	if (!is3Dmode)
	{
		double rouge = 0, vert = 0, bleu = 0;

		double r = (double)(myAmplitudes[0]*std::sin(myPulsations[0]*preciseIter + myPhases[0]));
		double g = (double)(myAmplitudes[1]*std::sin(myPulsations[1]*preciseIter + myPhases[1]));
		double bl = (double)(myAmplitudes[2]*std::sin(myPulsations[2]*preciseIter + myPhases[2]));

		fractal = Color(r, g, bl);  
	}
	else
	{
		double rouge = 0, vert = 0, bleu = 0;

		double r = (double)(myAmplitudes[0]*std::sin(myPulsations[0] *mode3D + myPhases[0]));
		double g = (double)(myAmplitudes[1]*std::sin(myPulsations[1] *mode3D + myPhases[1]));
		double bl = (double)(myAmplitudes[2]*std::sin(myPulsations[2] *mode3D + myPhases[2]));
		//System.out.println((int)(rouge*255.99));
		//rouge = (int)(r*255.99) > 255 ? 255 : (int)(r*255.99) < 0 ? 0 : (int)(r*255.99);
		//vert = (int)(g*255.99) > 255 ? 255 : (int)(g*255.99) < 0 ? 0 : (int)(g*255.99);
		//bleu = (int)(bl*255.99) > 255 ? 255 : (int)(bl*255.99) < 0 ? 0 : (int)(bl*255.99);

		fractal = Color(r, g, bl);   //On crée la couleur

		//argb = fractal.getRGB();
		//colorData = model.getDataElements(argb, null);
		//raster.setDataElements(i, j, colorData);
	}

	return fractal;
}

FACTORY_REGISTER_TYPE(Mandelbrot, Fractal)






/*
//
double saveX = x;
double saveY = y;
double saveA = a;
double saveB = b;
double saveSum = sum;
double p1x = a, p1y = b, p1z = sum;//std::log(std::sqrt(x*x + y*y));// / (std::pow(myBailout, 12));
Color col1 = myRenderer->computeColor(iterations, preciseIter, x, y, xPrime, yPrime);
int width = 800, height = 800;
double px = (a - XMIN) * width / (XMAX - XMIN);
double py = (b - YMIN) * height / (YMAX - YMIN);

a = XMIN + (px + 1.) * (XMAX - XMIN) / width;
b = YMIN + (py + 0.5) * (YMAX - YMIN) / height;

escapesToInfinity(a, b, iterations, preciseIter, x, y, xPrime, yPrime);
double p2x = a, p2y = b, p2z = sum;//std::log(std::sqrt(x*x + y*y));// / (std::pow(myBailout, 12));
Color col2 = myRenderer->computeColor(iterations, preciseIter, x, y, xPrime, yPrime);

a = XMIN + (px + 0.5) * (XMAX - XMIN) / width;
b = YMIN + (py + 1.) * (YMAX - YMIN) / height;
escapesToInfinity(a, b, iterations, preciseIter, x, y, xPrime, yPrime);
double p3x = a, p3y = b, p3z = sum;//std::log(std::sqrt(x*x + y*y));// / (std::pow(myBailout, 12));
Color col3 = myRenderer->computeColor(iterations, preciseIter, x, y, xPrime, yPrime);

double centerX = (XMAX + XMIN) / 2.;
double centerY = (YMAX + YMIN) / 2.;
double lightZ = 100. * std::max(p1z, std::max(p2z, p3z));

double ux = p2x - p1x, uy = p2y - p1y, uz = p2z - p1z;
double norm = std::sqrt(ux * ux + uy * uy + uz * uz);
ux /= norm; uy /= norm; uz /= norm;
double vx = p3x - p1x, vy = p3y - p1y, vz = p3z - p1z;
norm = std::sqrt(vx * vx + vy * vy + vz * vz);
vx /= norm; vy /= norm; vz /= norm;
//std::cout << x << " " << y << " " << ux << " " << uy << " " << uz << " " << vx << " " << vy << " " << vz << std::endl;

a = saveA;
b = saveB;
x = saveX;
y = saveY;

double nx = uy * vz - uz * vy;
double ny = uz * vx - ux * vz;
double nz = ux * vy - uy * vx;

norm = std::sqrt(nx * nx + ny * ny + nz * nz);
nx /= norm; ny /= norm; nz /= norm;

double lightVecX = centerX - a, lightVecY = centerY - b, lightVecZ = lightZ - p1z;
norm = std::sqrt(lightVecX * lightVecX + lightVecY * lightVecY + lightVecZ * lightVecZ);
lightVecX /= norm; lightVecY /= norm; lightVecZ /= norm;

double lightIntensity = 5;//00. / (norm * norm);
double dot = lightVecX * nx + lightVecY * ny + lightVecZ * nz;
dot = dot < 0 ? 0 : dot;
preciseIter = saveSum;
//std::cout << nx << " " << ny << " " << nz << " " << dot << std::endl;

Color finalCol = (col1 + col2 + col3) / 3.;
//if(finalCol.r > 1. || finalCol.g >  1|| finalCol.b > 1)
//	std::cout << finalCol << std::endl;
QColor qcol(finalCol.r * 255, finalCol.g * 255, finalCol.b * 255);
qcol.toHsv();
qreal h, s, v;
qcol.getHsvF(&h, &s, &v);
v *= lightIntensity * std::abs(dot);
qcol.setHsvF(h, s, v);
return Color(qcol.redF(), qcol.greenF(), qcol.blueF());
//return Color(r, g, bl);
//return (col1 + col2 + col3) / 3. * lightIntensity * std::abs(dot);
return myRenderer->computeColor(iterations, preciseIter, x, y, xPrime, yPrime);// *lightIntensity * std::abs(dot);*/