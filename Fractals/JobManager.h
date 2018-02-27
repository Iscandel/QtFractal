#pragma once

#include "Job.h"

#include <vector>
#include <queue>
#include <thread>
#include <mutex>

#include <QObject>

///////////////////////////////////////////////////////////////////////////////
/// \brief This class allows multithreaded computation of image chunks
///////////////////////////////////////////////////////////////////////////////
class JobManager : public QObject
{
public:
	Q_OBJECT

public:
	void setJoinMode(bool join) { myIsJoinMode = join; }

signals:
	void signalComputationAdvances(int perc);
	void signalJobsDone();

protected:
	void dispatchComputationAdvances(int perc);
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
	int remainingTasks();

	///////////////////////////////////////////////////////////////////////////////
	/// Pauses the program execution until the end of all the jobs.
	///////////////////////////////////////////////////////////////////////////////
	void join();

	bool isFinished();

	void addJobs(const std::vector<std::shared_ptr<Job> >& jobs, std::function<void()> callback);

	//void stopJobs();

	void initJobs();
	
	void jobRun();

	void destroyThreads();

	void showProgress();

	void setShowProgress(bool show) { myIsShowProgress = show; }

	void jobsDone();

protected:
	int myThreadNumber;

	std::vector<std::shared_ptr<std::thread> > myThreads;
	std::mutex myMutex;
	std::mutex myRemainingTasksMutex;
	std::mutex myProgressMutex;

	int myNumberRunning;
	std::vector<std::shared_ptr<Job> > myJobs;

	bool myIsShowProgress;

	int myJobsDone;
	int myTotalJobs;
	int myCoeff;
	double myShowValue;

	bool myIsJoinMode;

	std::function<void()> myEndCallback;
};


