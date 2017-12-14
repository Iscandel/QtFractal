#pragma once

#include "Array2D.h"
#include "FractalComputationListener.h"
#include "Parameters.h"

#include <memory>

#include <QObject>

class Fractal : public QObject
{
	Q_OBJECT

public:
	typedef std::shared_ptr<Fractal> ptr;
public:
	Fractal(QObject *parent = nullptr);
	~Fractal();

	//virtual void compute(const Parameters& params, Array2D<Color>& out) = 0;
	virtual void compute(const Parameters& params) = 0;

	void addAdvanceListener(QObject* listener);//FractalComputationListener* listener);

	void setArray(Array2D<Color>& array) { myArray = &array; }

signals:
	void signalComputationAdvances(int perc);

protected:
	void dispatchComputationAdvances(int perc);

protected:
//	std::vector<FractalComputationListener*> myListeners;
	Array2D<Color>* myArray;

	//boost::signals2::signal<void(int) > mySig;
};
