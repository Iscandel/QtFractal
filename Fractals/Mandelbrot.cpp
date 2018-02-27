#include "Mandelbrot.h"

#include "ObjectFactoryManager.h"

Mandelbrot::Mandelbrot(const Parameters& params)
:myIsLogLog(params.getBool("logLog", false))
,myMaxIt(params.getInt("maxIter", 100))
,myRefreshFrequency(10)
,XMIN(params.getDouble("xmin", -2.))
,XMAX(params.getDouble("xmax", 2.))
,YMIN(params.getDouble("ymin", -2.))
,YMAX(params.getDouble("ymax", 2.))
,myRenderer(params.getString("renderer", "Black & white"))
{
	initRenderer(myRenderer, params);
}


Mandelbrot::~Mandelbrot()
{
}

void Mandelbrot::initRenderer(const std::string& renderer, const Parameters& params)
{
	if (renderer == "Predefined")
	{
		myFractalColor = params.getColor("fractalColor", Color());
		myIterationsColors.push_back(Color(1., 0., 0.));
		myIterationsColors.push_back(Color(1., 0.5, 0.));
		myIterationsColors.push_back(Color(1., 1., 0.));
		myIterationsColors.push_back(Color(0., 1., 0.));
		myIterationsColors.push_back(Color(0., 0., 1.));
			
	}
	else if (renderer == "Random")
	{
		myFractalColor = params.getColor("fractalColor", Color());
		std::vector<boost::any> tmp = params.getVector("iterationColors", std::vector<boost::any>());
		for (auto elem : tmp) {
			myIterationsColors.push_back(boost::any_cast<Color>(elem));
		}
	}
	else if (renderer == "Sine")
	{
		myFractalColor = params.getColor("fractalColor", Color());
		myIsMode3D = params.getBool("isMode3D", false);
		std::vector<boost::any> tmp = params.getVector("amplitudes", std::vector<boost::any>());
		for (auto elem : tmp)
			myAmplitudes.push_back(boost::any_cast<double>(elem));
		
		tmp = params.getVector("phases", std::vector<boost::any>());
		for (auto elem : tmp)
			myPhases.push_back(boost::any_cast<double>(elem));
		
		tmp = params.getVector("pulsations", std::vector<boost::any>());
		for (auto elem : tmp)
			myPulsations.push_back(boost::any_cast<double>(elem));

	}
	else if (renderer == "Black & white")
	{
	}
	else
	{
		ILogger::log() << "unknown renderer " << renderer << "\n";
	}
}

void Mandelbrot::computeFull(const Parameters& params)//, Array2D<Color>& out)
{
	Array2D<Color>& out = *myArray;

	const double XMIN = params.getDouble("xmin", -2.);
	const double XMAX = params.getDouble("xmax", 2.);
	const double YMIN = params.getDouble("ymin", -2.);
	const double YMAX = params.getDouble("ymax", 2.);
	myIsLogLog = params.getBool("logLog", false);
	myMaxIt = params.getInt("maxIter", 100);
	int width = out.getWidth();
	int height = out.getHeight();
	
	//for (int i = 0; i < 6;i++)          //On sauvegarde le tableau de couleurs de l'objet Infos
	//	Couleurs[i] = Infos.getCouleur(i);

	//BufferedImage image = new BufferedImage(largeur, hauteur, BufferedImage.TYPE_INT_ARGB);
	////création de l’image au moyen de la classe BufferedImage
	//WritableRaster raster = image.getRaster();
	////appel de la méthode getRaster() afin d’obtenir un objet de type WritableRaster, vous    
	////permettant d’accéder aux pixels de l’image et de les modifier.
	//ColorModel model = image.getColorModel(); //renvoie le modèle de couleur de l’image       
	//										  //mémorisée.

	//this.maxIterations = Infos.getIterations();    //Sauvegarde du nombre max d'itérations
	//fractalColor = Couleurs[5];                   //Couleur de l'Ensemble
	//int argb = fractalColor.getRGB();             //Renvoie le code RGB de la couleur
	//Object colorData = model.getDataElements(argb, null);
	//this.typeRepresentation = Infos.getTypeRepresentation();
	//System.out.println(Infos.getTypeRepresentation());

	int cpt = 0;  //Un compteur, pour la barre de progression
	int coeffRefresh = 0;

	for (int i = 0; i < width; i++)		//boucle sur tous les pixels de l’image
	{
		for (int j = 0; j < height; j++)
		{
			//if (Stop.getStop())    //Si on a cliqué sur Stop
			//{
			//	i = largeur - 1;  //On passe aux derniers pixels de l'image, pour arrêter. On pourrait aussi faire un break
			//	j = hauteur - 1;
			//	/*On prévient l'utilisateur*/
			//	JOptionPane.showMessageDialog(null,
			//		"Interruption du calcul.", "Information",
			//		JOptionPane.INFORMATION_MESSAGE);
			//}

			/*On calcule le point courant. Il est situé entre XMIN et XMAX (resp. YMIN et YMAX),
			*  et il y a largeur points entre XMIN et XMAX (resp. longueur points entre YMIN etYMAX)*/
			double a = XMIN + i * (XMAX - XMIN) / width;
			double b = YMIN + j * (YMAX - YMIN) / height;
			double preciseIter;
			int iterations;
			if (!escapesToInfinity(a, b, iterations, preciseIter))
			{
				//argb = fractalColor.getRGB();   //Affecte le code RGB à un entier (compris entre 0 et 256^3)

				out(i, j) = Color(1., 0., 0.);
			}

			else  //Si ça ne diverge pas
			{
				//if (typeRepresentation == "Dégradé de gris") //On regarde le mode de représentation graphique choisi -Gris ici-
				{
					double coeff = 255 / myMaxIt;    //On calcule le coefficient, pour la couleur
					int rgb;

					if (!myIsLogLog)
						rgb = (int)(iterations*coeff);
					else  //Adoucissement log-log
					{
						double fin = preciseIter - iterations;
						double coeff2 = fin *coeff;
						rgb = (int)((iterations*coeff) + coeff2);
						rgb = rgb > 255 ? 255 : rgb;
					}

					/*On détermine la couleur pour le point en cours de calcul,
					dépendante du nombre d'itérations*/
					Color fractal = Color(rgb / 255.);

					out(i, j) = fractal;

					//argb = fractal.getRGB();    //On récupère le code RGB de la couleur
					//colorData = model.getDataElements(argb, null);
					//raster.setDataElements(i, j, colorData);
				}
			}
			int perc = (int)(((double)cpt / (width * height)) * 100);
			if (perc > myRefreshFrequency * coeffRefresh)
			{
				dispatchComputationAdvances(perc);
				coeffRefresh++;
			}
			cpt++;
		}
	}
}

Color Mandelbrot::computePixel(double a, double b, const Parameters& params)//, Array2D<Color>& out)
{
	myIsLogLog = params.getBool("logLog", false);
	myMaxIt = params.getInt("maxIter", 100);

	double preciseIter;
	int iterations;
	if (!escapesToInfinity(a, b, iterations, preciseIter))
	{
		return myFractalColor;
	}
	else  //Si ça ne diverge pas
	{
		if (myRenderer == "Black and white")
			return blackAndWhiteRenderer(iterations, preciseIter);
		else if (myRenderer == "Predefined")
			return predefinedAndRandomRenderer(iterations, preciseIter);
		else if (myRenderer == "Random")
			return predefinedAndRandomRenderer(iterations, preciseIter);
		else if (myRenderer == "Sine")
			return sineRenderer(iterations, preciseIter, false);

		//if (typeRepresentation == "Dégradé de gris") //On regarde le mode de représentation graphique choisi -Gris ici-
		{
			double coeff = 255 / myMaxIt;    //On calcule le coefficient, pour la couleur
			int rgb;

			if (!myIsLogLog)
				rgb = (int)(iterations*coeff);
			else  //Adoucissement log-log
			{
				double fin = preciseIter - iterations;
				double coeff2 = fin *coeff;
				rgb = (int)((iterations*coeff) + coeff2);
				rgb = rgb > 255 ? 255 : rgb;
			}

			/*On détermine la couleur pour le point en cours de calcul,
			dépendante du nombre d'itérations*/
			return Color(rgb / 255.);
		}
	}
}

bool Mandelbrot::escapesToInfinity(double a, double b, int& iterations, double& preciseIter)
{
	double x = 0.0;
	double y = 0.0;
	double xPrime = 0;
	double yPrime = 0;
	//   int iterations = 0;
	iterations = 0;  //On fixe le nombre d'itérations à 0
	do
	{
		double xnew = x * x - y * y + a;
		double ynew = 2 * x * y + b;

		double _xPrime = 2.*(x*xPrime - y*yPrime) + 1.;
		double _yPrime = 2.*(x*yPrime + y*xPrime);

		x = xnew;
		y = ynew;
		xPrime = _xPrime;
		yPrime = _yPrime;
		iterations++;
		if (iterations == myMaxIt) return false;
	} while (x*x + y*y <= 4);//x <= 2 && y <= 2);

	if (myIsLogLog)
		preciseIter = iterations + 1 - std::log(std::log(std::sqrt(x*x + y*y))) / std::log(2);
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
	return true;
}

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

	if (myIsLogLog)  //Si adoucissement log-log choisi, calculs supplémentaires
	{
		double fin = preciseIter - iterations;

		coeffR = coeffR * fin;
		coeffG = coeffG * fin;
		coeffB = coeffB * fin;
		//red = (int)(red + coeffR) > 255 ? 255 : (int)(red + coeffR) < 0 ? 0 : (int)(red + coeffR);
		////System.out.println(rouge);
		//green = (int)(green + coeffG)> 255 ? 255 : (int)(green + coeffG)< 0 ? 0 : (int)(green + coeffG);
		//blue = (int)(blue + coeffB)> 255 ? 255 : (int)(blue + coeffB)< 0 ? 0 : (int)(blue + coeffB);
	}

	fractal = Color(red + coeffR, green + coeffG, blue + coeffB);   //On crée la couleur

	return fractal;
}

Color Mandelbrot::blackAndWhiteRenderer(int iterations, double preciseIter)
{
	double coeff = 255 / myMaxIt;    //On calcule le coefficient, pour la couleur
	int rgb;

	if (!myIsLogLog)
		rgb = (int)(iterations*coeff);
	else  //Adoucissement log-log
	{
		double fin = preciseIter - iterations;
		double coeff2 = fin *coeff;
		rgb = (int)((iterations*coeff) + coeff2);
		rgb = rgb > 255 ? 255 : rgb;
	}

	/*On détermine la couleur pour le point en cours de calcul,
	dépendante du nombre d'itérations*/
	return Color(rgb / 255.);
}

Color Mandelbrot::sineRenderer(int iterations, double preciseIter, bool is3Dmode)
{
	Color fractal;
	if (!is3Dmode)
	{
		double rouge = 0, vert = 0, bleu = 0;

		double r = (double)(myAmplitudes[0]*std::sin(myPulsations[0]*preciseIter + myPhases[0]));
		double g = (double)(myAmplitudes[1]*std::sin(myPulsations[1]*preciseIter + myPhases[1]));
		double bl = (double)(myAmplitudes[2]*std::sin(myPulsations[2]*preciseIter + myPhases[2]));
		//System.out.println((int)(rouge*255.99));
		//rouge = (int)(r*255.99) > 255 ? 255 : (int)(r*255.99) < 0 ? 0 : (int)(r*255.99);
		//vert = (int)(g*255.99) > 255 ? 255 : (int)(g*255.99) < 0 ? 0 : (int)(g*255.99);
		//bleu = (int)(bl*255.99) > 255 ? 255 : (int)(bl*255.99) < 0 ? 0 : (int)(bl*255.99);

		fractal = Color(r, g, bl);   //On crée la couleur
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