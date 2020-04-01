#include "Buddhabrot.h"

#include "job/BuddhabrotJob.h"
#include "factory/ObjectFactoryManager.h"

Buddhabrot::Buddhabrot(const Parameters& params)
	: myMaxItRed(params.getInt("maxIterRed", 200))
	, myMaxItGreen(params.getInt("maxIterGreen", 600))
	, myMaxItBlue(params.getInt("maxIterBlue", 300))
	, myRefreshFrequency(10)
	, myRenderer(params.getString("renderer", "Black & white"))
	//, myWidth(params.getInt("sizeY", 800)) //Switch X and Y to rotate the image
	//, myHeight(params.getInt("sizeX", 800))
	, myWidth(params.getInt("sizeX", 800))
	, myHeight(params.getInt("sizeY", 800))
	, myLightIntensity(params.getDouble("lightIntensity", 2.3))
{
	//std::string name = ObjectStaticType<Buddhabrot>::get();
	//Notifier::ptr notifier(new GeneralNotifier("Buddhabrot"));

	//myWindow->connect((QtUiNotifier*)notifier.get(), &QtUiNotifier::signalJobsDone, myWindow, &FractalWindow::computationEnds, Qt::DirectConnection);

	//ProgressNotifier::addNotifier(notifier);
	//ProgressNotifier::moveToFront(notifier->getName());

	//Temporary transpose
	//YMIN = params.getDouble("xmin", -2.);
	//YMAX = params.getDouble("xmax", 2.);
	//XMIN = params.getDouble("ymin", -2.);
	//XMAX = params.getDouble("ymax", 2.);

	auto tmp = new GeneralNotifier("buddhabrot");
	tmp->setOnJobEnded(std::bind(&Buddhabrot::postProcessing, this, std::placeholders::_1, std::placeholders::_2));
	Notifier::ptr notifier(tmp);
	ProgressNotifier::addNotifier(notifier);
	ProgressNotifier::moveToFront(tmp->getName());
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Buddhabrot::~Buddhabrot()
{
	ProgressNotifier::removeNotifier("buddhabrot");
}

//void Buddhabrot::addComputationEndsListener(QObject* listener)
//{
//	connect(&myManager, &JobManager::signalJobsDone, (Buddhabrot*) this, &Buddhabrot::postProcessing); //First to be called, important
//	Fractal::addComputationEndsListener(listener);
//}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Buddhabrot::compute(const Parameters& params, std::function<void()> callback)
{
	//myManager.setJoinMode(true);

	ILogger::log() << "Starting computation..\n";

	myImage->resize(myImage->getSizeY(), myImage->getSizeX());
	myWidth = myImage->getSizeX();
	myHeight = myImage->getSizeY();

	initialize(params);

	//ILogger::log() << "Elapsed time loading + acceleration structure : " << clock.elapsedTime() << "s.\n";

	ILogger::log() << "Creating jobs...\n";

	myManager.setThreadNumber(params.getInt("threadNumber", 1));

	int blockSizeX, blockSizeY;
	blockSizeX = blockSizeY = params.getInt("blockSize", 800);


	//local temp component images
	myImageRed =
		myImage->createSubImage(myImage->getSizeX(), myImage->getSizeY(), 0, 0);
	myImageGreen =
		myImage->createSubImage(myImage->getSizeX(), myImage->getSizeY(), 0, 0);
	myImageBlue =
		myImage->createSubImage(myImage->getSizeX(), myImage->getSizeY(), 0, 0);

	std::vector<std::shared_ptr<Job> > jobs;
	for (int currentY = 0; currentY < myImage->getSizeY(); currentY += blockSizeY)//myBlockSize.y())
	{
		//std::cout << currentY << std::endl;
		for (int currentX = 0; currentX < myImage->getSizeX(); currentX += blockSizeX)//myBlockSize.x())
		{
			//std::shared_ptr<Sampler> sampler(mySampler->clone());
			//sampler->seed(currentX, currentY);

			std::shared_ptr<Job> job(new BuddhabrotJob(currentX, currentY, blockSizeX, blockSizeY, this, params, myCamera, myImageRed, myImageGreen, myImageBlue));
			jobs.push_back(job);
		}
	}

	//std::thread render_thread([&] {
	//	myManager.addJobs(jobs, callback);
	//});

	myManager.setJobs(jobs, "Computation...");//, callback);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
std::vector<std::vector<TraceSample>> Buddhabrot::computePixel(double a, double b, const Parameters& params)
{

	/*On alloue une taille de tableau équivalente à la taille de l'image pour chacun des 3 tableaux*/
	//lesPointsR = new long[largeur][hauteur];
	//lesPointsG = new long[largeur][hauteur];
	//lesPointsB = new long[largeur][hauteur];

	std::vector<std::vector<TraceSample>> trace;
	trace.push_back(std::vector<TraceSample>());
	trace.push_back(std::vector<TraceSample>());
	trace.push_back(std::vector<TraceSample>());

	/* On boucle 3 fois. Le principe est que chaque tour de boucle va calculer
	* la valeur d'une composante pour chaque pixel de l'image: rouge, puis verte
	*  puis bleue. A la fin des 3 passages, on crée une couleur avec les 3 composantes,
	*  et ce pour chaque pixel. C'est le principe des images en fausse couleur*/
	for (int composante = 0; composante < 3; composante++)
	{
		if (composante == 0) myCurrentMaxIt = myMaxItRed;
		if (composante == 1) myCurrentMaxIt = myMaxItGreen;
		if (composante == 2) myCurrentMaxIt = myMaxItBlue;

		//for (int i = 0; i < myWidth * 10; i++)		//boucle sur tous les pixels de l’image
		//{
		//	for (int j = 0; j < my * 10; j++)
		//	{
		//		double a = XMIN + i * (XMAX - XMIN) / (largeur * 10);
		//		double b = YMIN + j * (YMAX - YMIN) / (hauteur * 10);

				/*Si le point ne diverge pas, on réappelle la fonction*/
				if (escapesToInfinity(a, b, false, composante, trace))
				{
					escapesToInfinity(a, b, true, composante, trace);
				}
			//}
		//}
	}

	return trace;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void Buddhabrot::postProcessing(const std::string&, bool)
{
	std::cout << "post processing" << std::endl;

	//myImageRed->postProcessColor();
	//myImageGreen->postProcessColor();
	//myImageBlue->postProcessColor();
	myImage->resize(myImage->getSizeY(), myImage->getSizeX());
	myWidth = myImage->getSizeX();
	myHeight = myImage->getSizeY();
	//XMIN = params.getDouble("xmin", -2.);
	//XMAX = params.getDouble("xmax", 2.);
	//YMIN = params.getDouble("ymin", -2.);
	//YMAX = params.getDouble("ymax", 2.);

	for (int y = 0; y < myImage->getSizeY(); y++)
	{
		for (int x = 0; x < myImage->getSizeX(); x++)
		{
			(*myImage)(x, y) = Color((*myImageRed)(y, x).r, (*myImageGreen)(y, x).g, (*myImageBlue)(y, x).b);
			//(*myImage)(x, y) = Color((*myImageRed)(x, y).r, (*myImageGreen)(x, y).g, (*myImageBlue)(x, y).b);
		}
	}

	Image& tmpImage = (*myImage);
	double maxR = tmpImage(0, 0).r;      //On cherche le max du tableau  
	for (int i = 0; i < myWidth; i++)		//boucle sur tous les pixels de l’image
	{
		for (int j = 0; j < myHeight; j++)
		{
			maxR = std::max(maxR, tmpImage(i, j).r);
		}
		//coeffR = 255.0 / maxR;   //On le normalise par 1/255
	}

	double maxG = tmpImage(0, 0).g;
	for (int i = 0; i < myWidth; i++)		//boucle sur tous les pixels de l’image
	{
		for (int j = 0; j < myHeight; j++)
		{
			maxG = std::max(maxG, tmpImage(i, j).g);
		}
	}
	//coeffG = 255.0 / maxG;

	double maxB = tmpImage(0, 0).b;
	for (int i = 0; i < myWidth; i++)		//boucle sur tous les pixels de l’image
	{
		for (int j = 0; j < myHeight; j++)
		{
			maxB = std::max(maxB, tmpImage(i, j).b);
		}
	}
	//coeffB = 255.0 / maxB;

	for (int i = 0; i < myWidth; i++)		//boucle sur tous les pixels de l’image
	{
		for (int j = 0; j < myHeight; j++)
		{

			double t1 = tmpImage(i, j).r / (maxR / myLightIntensity);
			if (t1 > 1)
				t1 = 1;
			double t2 = tmpImage(i, j).g / (maxG / myLightIntensity);
			if (t2 > 1)
				t2 = 1;
			double t3 = tmpImage(i, j).b / (maxB / myLightIntensity);
			if (t3 > 1)
				t3 = 1;

			Color color(t1, t2, t3);
			tmpImage(i, j) = color;
			//myImage

			//(*myImage)(i, j) = Color((*myImageRed)(i, j).r, (*myImageGreen)(i, j).g, (*myImageBlue)(i, j).b);
		}
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool Buddhabrot::escapesToInfinity(double a, double b, bool passage2, int composante, std::vector<std::vector<TraceSample>>& trace)
{
	double x = 0.0;
	double y = 0.0;
	int iterations = 0;  //On fixe le nombre d'itérations à 0
	do
	{
		double xnew = x * x - y * y + a;
		double ynew = 2 * x * y + b;
		x = xnew;
		y = ynew;

		if (passage2 == true && iterations >= 2)
		{
			Point2r p = myCamera->getIndexSpacePoint(x, y);

			if (p.x() > 0 && p.x() < myImage->getSizeX() && p.y() > 0 && p.y() < myImage->getSizeY())
			//if (x > XMIN && x < XMAX && y > YMIN && y < YMAX)
			{
				//double n =(((x - XMIN) * myWidth) / (XMAX - XMIN));
				//double m = (((y - YMIN) * myHeight) / (YMAX - YMIN));
			
				trace[composante].push_back(TraceSample{ p.x(), p.y() });
				
			}
		}

		iterations++;
		if (iterations == myCurrentMaxIt) return false;
	} while (x*x + y*y <= 4);// <= 2 && y <= 2);
	return true;
}

bool Buddhabrot::isComputing()
{
	return !myManager.isIdle();
}

FACTORY_REGISTER_TYPE(Buddhabrot, Fractal)