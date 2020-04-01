#pragma once
#include <memory>
#include <string>
#include <functional>

#include <QObject>

class Notifier
{
public:
	typedef std::unique_ptr<Notifier> ptr;
	
public:
	Notifier(const std::string& name = "")
		:myName(name)
	{
	}

	//Mandatory virtual destructor for use with unique_ptr
	virtual ~Notifier() {}

	const std::string& getName() const { return myName; }

	virtual void reportProgress(const std::string& message, float value) = 0;
	virtual void reportJobsEnded(const std::string& message, bool cancelled) = 0;
	virtual void reportDataModified(int minX, int maxX, int minY, int maxY, int overlapX, int overlapY, const std::vector<uint8_t>& modifiedData) = 0;

protected:
	std::string myName;
};

class QtUiNotifier : public QObject, public Notifier
{
public:
	Q_OBJECT
public:
	typedef std::unique_ptr<QtUiNotifier> ptr;

public:
	QtUiNotifier(const std::string& name = "")
		:Notifier(name)
	{
	}

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

class GeneralNotifier : public Notifier
{
public:
	typedef std::unique_ptr<GeneralNotifier> ptr;

public:
	GeneralNotifier(const std::string& name = "")
		:Notifier(name)
	{
	}

	void setOnProgress(const std::function<void(const std::string&, float)>& f) {
		myOnProgress = f;
	}
	void setOnJobEnded(const std::function<void(const std::string&, bool)>& f) {
		myOnJobEnded = f;
	}
	void setOnDataModified(const std::function<void(int minX, int maxX, int minY, int maxY, 
		int overlapX, int overlapY, const std::vector<uint8_t>& modifiedData)>& f) {
		myOnDataModified = f;
	}

	virtual void reportProgress(const std::string& message, float value) override { 
		if(myOnProgress)
			myOnProgress(message, value); 
	}

	virtual void reportJobsEnded(const std::string& message, bool cancelled) override {
		if(myOnJobEnded)
			myOnJobEnded(message, cancelled);
	}

	virtual void reportDataModified(int minX, int maxX, int minY, int maxY, int overlapX, int overlapY, const std::vector<uint8_t>& modifiedData) override {
		if(myOnDataModified)
			myOnDataModified(minX, maxX, minY, maxY, overlapX, overlapY, modifiedData);
	}

protected:
	std::function<void(const std::string&, float)> myOnProgress;
	std::function<void(const std::string&, bool)> myOnJobEnded;
	std::function<void(int minX, int maxX, int minY, int maxY, int overlapX, 
		int overlapY, const std::vector<uint8_t>& modifiedData)> myOnDataModified;
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

	static void removeNotifier(const std::string& name)
	{
		int cpt = 0;
		for (auto& n : myNotifiers)
		{
			if (n->getName() == name) {
				myNotifiers.erase(myNotifiers.begin() + cpt);
				return;
			}
			cpt++;
		}
	}

	static void clearNotifiers()
	{
		myNotifiers.clear();
	}

	static void moveToFront(const std::string& name)
	{
		for (auto& notifier : myNotifiers) {
			if (notifier->getName() == name) {
				std::swap(notifier, myNotifiers.front());
				return;
			}
		}
	}

	void setTotal(float total) { myTotal = total; }

	void reportProgress(const std::string& message, float value);
	void reportJobsEnded(const std::string& message, bool cancelled);
	void reportDataModified(int minX, int maxX, int minY, int maxY, int overlapX, int overlapY, const std::vector<uint8_t>& modifiedData);

protected:
	float myTotal;
	static std::vector<Notifier::ptr> myNotifiers;
};

