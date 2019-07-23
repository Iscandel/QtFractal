#pragma once

#include "Job.h"

#include <vector>
#include <queue>
#include <thread>
#include <mutex>

#include <QObject>


#include "ProgressNotifier.h"

///////////////////////////////////////////////////////////////////////////////
/// \brief This class allows multithreaded computation of image chunks
///////////////////////////////////////////////////////////////////////////////
class JobManager
{


public:
	ProgressNotifier myProgress; //to change !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
public:
	void setJoinMode(bool join) { myIsJoinMode = join; }

//protected:
//	void dispatchComputationAdvances(int perc);
public:
	JobManager();
	~JobManager(void);


	///////////////////////////////////////////////////////////////////////////////
	/// Defines the number of threads to be used.
	///////////////////////////////////////////////////////////////////////////////
	void setThreadNumber(int number);

	///////////////////////////////////////////////////////////////////////////////
	/// Returns the number of threads to be used.
	/// \return Number of threads.
	///////////////////////////////////////////////////////////////////////////////
	int getThreadNumber() const {return myThreadNumber;}

	///////////////////////////////////////////////////////////////////////////////
	/// Returns the number of active tasks (threads).
	///////////////////////////////////////////////////////////////////////////////
	int remainingThreads();

	///////////////////////////////////////////////////////////////////////////////
	/// Pauses the program execution until the end of all the jobs.
	///////////////////////////////////////////////////////////////////////////////
	void join();

	bool isIdle();

	void addJobs(const std::vector<std::shared_ptr<Job> >& jobs, std::function<void()> callback);
	void setJobs(const std::vector<std::shared_ptr<Job> >& jobs, const std::string& progressMessage);//, std::function<void()> callback);

	//void stopJobs();

	void initJobs(const std::vector<std::shared_ptr<Job> >& jobs);
	
	void jobRun();

	void destroyThreads();

	void showProgress();

	void setShowProgress(bool show) { myIsShowProgress = show; }

	//void jobsDone();

	void cancelComputation(bool wait);

protected:
	int myThreadNumber;

	std::vector<std::shared_ptr<std::thread> > myThreads;
	std::mutex myMutex;
	std::mutex myRemainingTasksMutex;
	std::mutex myProgressMutex;

	int myNumberRunning;
	std::vector<std::shared_ptr<Job> > myJobs;

	bool myIsShowProgress;
	bool myIsCancelled;

	int myJobsDone;
	int myTotalJobs;
	int myCoeff;
	double myShowValue;

	bool myIsJoinMode;
	std::string myProgressMessage;

	//std::function<void()> myEndCallback;
};


