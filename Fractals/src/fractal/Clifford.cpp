#include "Clifford.h"

#include "factory/ObjectFactoryManager.h"
#include "job/CliffordJob.h"

Clifford::Clifford(const Parameters& params)
	:myMaxIt(100)
	, myProgress(0)
{
}


Clifford::~Clifford()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
std::vector<TraceSample> Clifford::computePixel(double _a, double _b, int maxIt)
{
	std::vector<TraceSample> trace;

	real a = 1.7;
	real b = 1.7;
	real c = 0.6;
	real d = 1.2;

	if (maxIt == 500) {
		a = 1.;
		b = -1.2;
		c = 2.1;
		d = -1.2;
	}
	if (maxIt == 1500) {
		a = 0.1;
		b = 0.6;
		c = -1.1;
		d = 2.4;
	}

	real x = _a;
	real y = _b;
	for (int i = 0; i < maxIt; i++)
	{
		real newX = std::sin(a * y) + c * cos(a * x);
		real newY = std::sin(b * x) + d * cos(b * y);

		Point2r p = myCamera->getIndexSpacePoint(newX, newY);

		if (p.x() > 0 && p.x() < myImage->getSizeX() && p.y() > 0 && p.y() < myImage->getSizeY())
			trace.push_back(TraceSample(p.x(), p.y()));

		x = newX;
		y = newY;
	}

	return trace;
}

void Clifford::compute(const Parameters& params, std::function<void()> callback)
{
	std::vector<std::shared_ptr<Job> > jobs;

	myManager.setThreadNumber(3);

	std::shared_ptr<Job> job(new CliffordJob(0, 0, myImage->getSizeX(), myImage->getSizeY(), this, params, myCamera, 1000, 5., myImage, Color(1., 0., 0.)));
	jobs.push_back(job);
	job = std::make_shared<CliffordJob>(0, 0, myImage->getSizeX(), myImage->getSizeY(), this, params, myCamera, 500, 5., myImage, Color(0., 1., 0.));
	jobs.push_back(job);
	job = std::make_shared<CliffordJob>(0, 0, myImage->getSizeX(), myImage->getSizeY(), this, params, myCamera, 1500, 4., myImage, Color(0., 0., 1.));
	jobs.push_back(job);

	////std::thread render_thread([&] {
	////	myManager.addJobs(jobs, callback);
	////});

	myManager.setJobs(jobs, "Computation...");//, callback);

	//int oversampling = 4;

	//for (int y = 0; y < myImage->getSizeY(); y++)
	//{
	//	std::cout << y << std::endl;
	//	for (int x = 0; x < myImage->getSizeX(); x++)
	//	{
	//		for (int i = 0; i < oversampling; i++)
	//		{
	//			for (int j = 0; j < oversampling; j++)
	//			{
	//				double xx = (double)x + (double)j / oversampling;
	//				double yy = (double)y + (double)i / oversampling;
	//				//for (int i = 0; i < mySampler->getSampleNumber(); i++)
	//				{
	//					//new
	//					Point2r worldPoint = myCamera->getWorldSpacePoint(xx, yy);
	//					auto trace = computePixel(worldPoint(0), worldPoint(1), Parameters());

	//					Color col(1., 0., 0.);
	//					for (int i = 0; i < trace.size(); i++)
	//					{
	//						myImage->addSample(trace[i].x, trace[i].y, col);
	//					}
	//					
	//					myMaxIt = 50;
	//					trace = computePixel(worldPoint(0), worldPoint(1), Parameters());
	//					
	//					col = Color(0., 1., 0.);
	//					for (int i = 0; i < trace.size(); i++)
	//					{
	//						myImage->addSample(trace[i].x, trace[i].y, col);
	//					}

	//					myMaxIt = 150;
	//					trace = computePixel(worldPoint(0), worldPoint(1), Parameters());

	//					col = Color(0., 0., 1.);
	//					for (int i = 0; i < trace.size(); i++)
	//					{
	//						myImage->addSample(trace[i].x, trace[i].y, col);
	//					}
	//				}
	//			}
	//		}
	//	}
	//}

	//real scale = 10.;
	//Image& tmpImage = (*myImage);
	//double maxValr = tmpImage(0, 0).r;      //On cherche le max du tableau  
	//for (int i = 0; i < myImage->getSizeX(); i++)		//boucle sur tous les pixels de l段mage
	//{
	//	for (int j = 0; j < myImage->getSizeY(); j++)
	//	{
	//		tmpImage.getPixel(i, j).myWeight = 1.;
	//		maxValr = std::max(maxValr, tmpImage(i, j).r);
	//	}
	//	//coeffR = 255.0 / maxR;   //On le normalise par 1/255
	//}

	////for (int i = 0; i < myImage->getSizeX(); i++)		//boucle sur tous les pixels de l段mage
	////{
	////	for (int j = 0; j < myImage->getSizeY(); j++)
	////	{

	////		tmpImage(i, j) /= (maxVal / scale);
	////	}
	////}

	////
	//double maxValg = tmpImage(0, 0).g;      //On cherche le max du tableau  
	//for (int i = 0; i < myImage->getSizeX(); i++)		//boucle sur tous les pixels de l段mage
	//{
	//	for (int j = 0; j < myImage->getSizeY(); j++)
	//	{
	//		tmpImage.getPixel(i, j).myWeight = 1.;
	//		maxValg = std::max(maxValg, tmpImage(i, j).g);
	//	}
	//	//coeffR = 255.0 / maxR;   //On le normalise par 1/255
	//}

	//double maxValb = tmpImage(0, 0).b;      //On cherche le max du tableau  
	//for (int i = 0; i < myImage->getSizeX(); i++)		//boucle sur tous les pixels de l段mage
	//{
	//	for (int j = 0; j < myImage->getSizeY(); j++)
	//	{
	//		tmpImage.getPixel(i, j).myWeight = 1.;
	//		maxValb = std::max(maxValb, tmpImage(i, j).b);
	//	}
	//	//coeffR = 255.0 / maxR;   //On le normalise par 1/255
	//}

	//Color maxVal(maxValr, maxValg, maxValb);

	//for (int i = 0; i < myImage->getSizeX(); i++)		//boucle sur tous les pixels de l段mage
	//{
	//	for (int j = 0; j < myImage->getSizeY(); j++)
	//	{

	//		tmpImage(i, j) /= (maxVal / scale);
	//	}
	//}

	//myProgress.reportJobsEnded("", false);

	//myImage->postProcessColor();
}

FACTORY_REGISTER_TYPE(Clifford, Fractal)