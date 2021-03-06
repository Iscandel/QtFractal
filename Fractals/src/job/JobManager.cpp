#include "JobManager.h"

//#include "Timer.h"
#include "tools/Logger.h"

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
JobManager::JobManager()
:myThreadNumber(0)
,myNumberRunning(0)
,myIsShowProgress(true)
,myJobsDone(0)
,myCoeff(0)
,myShowValue(0.02)
,myIsJoinMode(false)
, myProgress(0)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
JobManager::~JobManager(void)
{
	//delete myMutex;
	//delete myRemainingTasksMutex;

	destroyThreads();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void JobManager::setThreadNumber(int number)
{
	std::lock_guard<std::mutex> lock(myRemainingTasksMutex);

	if(myNumberRunning > 0)
	{
		ILogger::log() << "Cannot change the number of threads while some tasks are running.\n";
		return;
	}

	destroyThreads();

	myThreadNumber = number;

}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void JobManager::destroyThreads()
{
	for(unsigned int i = 0; i < myThreads.size(); i++)
	{
		if(myThreads[i]->joinable())
			myThreads[i]->join();
		//delete myThreads[i];
	}

	myThreads.clear();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool JobManager::isIdle()
{
	std::lock_guard<std::mutex> lock(myRemainingTasksMutex);

	return myNumberRunning <= 0;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
int JobManager::remainingThreads()
{
	std::lock_guard<std::mutex> lock(myRemainingTasksMutex);

	return myNumberRunning;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void JobManager::addJobs(const std::vector<std::shared_ptr<Job> >& jobs, std::function<void()> callback)
{
	//Timer clock;

	std::lock_guard<std::mutex> lock(myMutex);
	//Enqueue jobs
	for(unsigned int i = 0; i < jobs.size(); i++)
	{
		myJobs.push_back(jobs[i]);
	}

	//myTotalJobs = myJobs.size();

	//myIsShowProgress &= myTotalJobs > 2 ? true : false;

	//myEndCallback = callback;

	//myProgress.setTotal(myTotalJobs);

	////Single threaded processing
	////if(myThreadNumber == 1)
	////{
	////	myNumberRunning = myThreadNumber;
	////	for(unsigned int i = 0; i < jobs.size(); i++)
	////	{
	////		myJobs[i]->run();
	////	}
	////	myNumberRunning = 0;
	////}
	////else
	////{
	//	//if(myThreads.size() == 0) 
	//	{
	//		initJobs();
	//	}

	//	//If the job manager is run in a threaded way, join can be called (and the end callback will be called after)
	//	if(myIsJoinMode)
	//		join();

	//	//jobsDone();

	//	//callback();
	////}

	////ILogger::log() << "Render time : " << clock.elapsedTime() << " s.\n";
}

void JobManager::setJobs(const std::vector<std::shared_ptr<Job> >& jobs, const std::string& progressMessage)//, std::function<void()> callback)
{
	//Timer clock;
	myProgressMessage = progressMessage;
	//Enqueue jobs
	//for (unsigned int i = 0; i < jobs.size(); i++)
	//{
	//	myJobs.push_back(jobs[i]);
	//}

	//myTotalJobs = myJobs.size();

	//myIsShowProgress &= myTotalJobs > 2 ? true : false;

	//myEndCallback = callback;

	//myProgress.setTotal(myTotalJobs);
	//

	//Single threaded processing
	//if(myThreadNumber == 1)
	//{
	//	myNumberRunning = myThreadNumber;
	//	for(unsigned int i = 0; i < jobs.size(); i++)
	//	{
	//		myJobs[i]->run();
	//	}
	//	myNumberRunning = 0;
	//}
	//else
	//{
	//if(myThreads.size() == 0) 
	{
		initJobs(jobs);
	}

	//If the job manager is run in a threaded way, join can be called (and the end callback will be called after)
	if (myIsJoinMode)
		join();

	//jobsDone();

	//callback();
	//}

	//ILogger::log() << "Render time : " << clock.elapsedTime() << " s.\n";
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void JobManager::initJobs(const std::vector<std::shared_ptr<Job> >& jobs)
{
	if (myThreads.size() != 0)
	{
		for (int i = 0; i < myThreads.size(); i++)
		{
			if (myThreads[i]->joinable())
				myThreads[i]->join();
		}
	}
	myThreads.clear();

	myIsCancelled = false;
	myCoeff = 0;
	myJobsDone = 0.;
	myNumberRunning = myThreadNumber;

	//
	myJobs.clear();

	//Enqueue jobs
	for (unsigned int i = 0; i < jobs.size(); i++)
	{
		myJobs.push_back(jobs[i]);
	}

	myTotalJobs = myJobs.size();

	myIsShowProgress &= myTotalJobs > 2 ? true : false;

	//myEndCallback = callback;

	myProgress.setTotal(myTotalJobs);
	//

	myThreads.resize(myThreadNumber);
	for(int i = 0; i < myThreadNumber; i++) 
	{
		myThreads[i].reset(new std::thread(&JobManager::jobRun, this));
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void JobManager::join()
{
	bool someRunning = !isIdle();
	for (int i = 0; i < myThreads.size(); i++)
	{
		if (myThreads[i]->joinable())
			myThreads[i]->join();
	}

	myThreads.clear();

	if(someRunning)
		myProgress.reportJobsEnded("", myIsCancelled);
	//myEndCallback();
}

//void JobManager::stopJobs()
//{
//	for(unsigned int i = 0; i < myJobs.size(); i++)
//	{
//		myJobs[i]->stop();
//	}
//
//	for(unsigned int i = 0; i < myThreadNumber; i++) 
//	{
//		myThreads[i]->Wait();
//	}
//}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void JobManager::jobRun()
{
	while(true)
	{
		std::shared_ptr<Job> job = NULL;
		{	
			std::lock_guard<std::mutex> lock(myMutex);

			if(myJobs.size() == 0 || myIsCancelled)
				break;
	
			job = myJobs.back();
			myJobs.pop_back();
		}

		job->run();

		if (myIsShowProgress)
		{
			showProgress();
		}
	}


	std::lock_guard<std::mutex> lock(myRemainingTasksMutex);
	myNumberRunning--;
	if (myNumberRunning == 0 && !myIsJoinMode)
	{
		myProgress.reportJobsEnded("", myIsCancelled);
		//jobsDone();
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
//void JobManager::jobsDone()
//{
//	//myThreads.clear();
//	emit signalJobsDone();
//	//myEndCallback();
//}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void JobManager::cancelComputation(bool wait)
{
	myIsCancelled = true;
	if(wait)
		join();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void JobManager::showProgress()
{
	std::lock_guard<std::mutex> lock(myProgressMutex);
	myJobsDone++;

	if ((double)myJobsDone / myTotalJobs > myShowValue * myCoeff)
	{
		myProgress.reportProgress(myProgressMessage, myJobsDone);
		//double perc = myShowValue * myCoeff * 100;
		//dispatchComputationAdvances(perc);
		//ILogger::log() << perc << "%\n";
		myCoeff++;
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
//void JobManager::dispatchComputationAdvances(int perc)
//{
//	emit signalComputationAdvances(perc);
//}