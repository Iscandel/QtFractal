#include "ProgressNotifier.h"

std::vector<Notifier::ptr> ProgressNotifier::myNotifiers;

ProgressNotifier::ProgressNotifier(float total)
:myTotal(total)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
ProgressNotifier::~ProgressNotifier()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ProgressNotifier::reportProgress(const std::string& message, float advance)
{
	float perc = advance / myTotal * 100.f;
	for (int i = 0; i <  myNotifiers.size(); i++)
		myNotifiers[i]->reportProgress(message, perc);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ProgressNotifier::reportJobsEnded(const std::string& message, bool cancelled)
{
	for (int i = 0; i < myNotifiers.size(); i++)
		myNotifiers[i]->reportJobsEnded(message, cancelled);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void ProgressNotifier::reportDataModified(int minX, int maxX, int minY, int maxY, int overlapX, int overlapY, const std::vector<uint8_t>& modifiedData)
{
	for (int i = 0; i < myNotifiers.size(); i++)
		myNotifiers[i]->reportDataModified(minX, maxX, minY, maxY, overlapX, overlapY, modifiedData);
}