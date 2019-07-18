#pragma once
#include <memory>
#include <string>

#include <QObject>

class Notifier
{
public:
	typedef std::unique_ptr<Notifier> ptr;
	
public:
	//Mandatory virtual destructor for use with unique_ptr
	virtual ~Notifier() {}

	virtual void reportProgress(const std::string& message, float value) = 0;
	virtual void reportJobsEnded(const std::string& message, bool cancelled) = 0;
	virtual void reportDataModified(int minX, int maxX, int minY, int maxY, int overlapX, int overlapY, const std::vector<uint8_t>& modifiedData) = 0;
};

class QtUiNotifier : public QObject, public Notifier
{
public:
	Q_OBJECT
public:
	typedef std::unique_ptr<QtUiNotifier> ptr;

	virtual void reportProgress(const std::string& message, float value) override { emit signalComputationAdvances(QString::fromStdString(message), value); }
	virtual void reportJobsEnded(const std::string& message, bool cancelled) override {
		emit signalJobsDone(QString::fromStdString(message), cancelled);
	}

	virtual void reportDataModified(int minX, int maxX, int minY, int maxY, int overlapX, int overlapY, const std::vector<uint8_t>& modifiedData) override {
		emit signalReportDataModified(minX, maxX, minY, maxY, overlapX, overlapY, modifiedData);
	}

signals:
	void signalComputationAdvances(const QString& message, float value);
	void signalJobsDone(const QString& message, bool cancelled);
	void signalReportDataModified(int minX, int maxX, int minY, int maxY, int overlapX, int overlapY, const std::vector<uint8_t>& modifiedData);
};

class ProgressNotifier
{
public:
	ProgressNotifier(float total);
	~ProgressNotifier();

	static void addNotifier(Notifier::ptr& notifier)
	{
		myNotifiers.push_back(std::move(notifier));
	}

	static void clearNotifiers()
	{
		myNotifiers.clear();
	}

	void setTotal(float total) { myTotal = total; }

	void reportProgress(const std::string& message, float value);
	void reportJobsEnded(const std::string& message, bool cancelled);
	void reportDataModified(int minX, int maxX, int minY, int maxY, int overlapX, int overlapY, const std::vector<uint8_t>& modifiedData);

protected:
	float myTotal;
	static std::vector<Notifier::ptr> myNotifiers;
};

