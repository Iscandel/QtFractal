#pragma once

#include "Array2D.h" //old
#include "Image.h"
#include "FractalComputationListener.h"
#include "JobManager.h"
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

	//virtual void computeFull(const Parameters& params) = 0; //à suppr

	//virtual void compute(const Parameters& params, Array2D<Color>& out) = 0;
	virtual void compute(const Parameters& params, std::function<void()> callback) = 0;

	void addAdvanceListener(QObject* listener);//FractalComputationListener* listener);
	void addComputationEndsListener(QObject* listener);//FractalComputationListener* listener);

	void setArray(Array2D<Color>& array) { myArray = &array; }

	void setImage(Image::ptr image) { myImage = image; }

	virtual void initialize(const Parameters&) {}

signals:
	void signalComputationAdvances(int perc);

protected:
	void dispatchComputationAdvances(int perc);

protected:
//	std::vector<FractalComputationListener*> myListeners;
	Array2D<Color>* myArray; //old

	Image::ptr myImage;

	JobManager myManager;

	//boost::signals2::signal<void(int) > mySig;
};

class GenericParallelizableFractal : public Fractal
{
public:
	virtual void compute(const Parameters& params, std::function<void()> callback) override;
	virtual Color computePixel(double x, double y, const Parameters& params) = 0;
};
