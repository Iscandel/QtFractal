#include "Fractal.h"

#include "job/FractalJob.h"
#include "tools/Logger.h"


Fractal::Fractal()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
Fractal::~Fractal()
{
}

//void Fractal::addAdvanceListener(QObject* listener)//FractalComputationListener* listener)
//{
//	bool res = connect(&myManager, SIGNAL(signalComputationAdvances(int)), listener, SLOT(computationAdvances(int)));
//	std::cout << res << std::endl;
//
//	//myManager.signalComputationAdvances(10);
//	//old
//	//connect(this, SIGNAL(signalComputationAdvances(int)), listener, SLOT(computationAdvances(int)));
//
//	//myListeners.push_back(listener); /old 2
//}

//void Fractal::addComputationEndsListener(QObject* listener)
//{
//	connect(&myManager, &JobManager::signalJobsDone, (FractalWindow*)listener, &FractalWindow::computationEnds);
//}

//void Fractal::addAdvanceListener2(ProgressDialog& obj)//FractalComputationListener* listener)
//{
//	mySig.connect(boost::bind(&ProgressDialog::computationAdvances, &obj, _1));
//}


//void Fractal::dispatchComputationAdvances(int perc)
//{
//	emit signalComputationAdvances(perc);
//	//for (FractalComputationListener* listener : myListeners)
//	//{
//	//	listener->computationAdvances(perc);
//	//}
//}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void GenericParallelizableFractal::compute(const Parameters& params, std::function<void()> callback)
{
	ILogger::log() << "Starting computation..\n";

	initialize(params);



	ILogger::log() << "Creating jobs...\n";

	myManager.setThreadNumber(params.getInt("threadNumber", 1));

	int blockSizeX, blockSizeY;
	blockSizeX = blockSizeY = params.getInt("blockSize", 32);

	std::vector<std::shared_ptr<Job> > jobs;
	for (int currentY = 0; currentY < myImage->getSizeY(); currentY += blockSizeY)//myBlockSize.y())
	{
		for (int currentX = 0; currentX < myImage->getSizeX(); currentX += blockSizeX)//myBlockSize.x())
		{
			//std::shared_ptr<Sampler> sampler(mySampler->clone());
			//sampler->seed(currentX, currentY);

			std::shared_ptr<Job> job(new GenericFractalJob(currentX, currentY, blockSizeX, blockSizeY, this, params, myImage, myCamera));
			jobs.push_back(job);
		}
	}

	myManager.setJobs(jobs, "Computation...");//, callback);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void GenericParallelizableFractal::cancelComputation(bool wait)
{
	myManager.cancelComputation(wait);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool GenericParallelizableFractal::isComputing()
{
	return !myManager.isIdle();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void GenericParallelizableFractal::clean()
{
	myManager.destroyThreads();
}