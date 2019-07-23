#pragma once

#include "core/Array2D.h" //old
#include "core/Image.h"
//#include "core/FractalComputationListener.h"
#include "job/JobManager.h"
#include "core/MathParser.h"
#include "core/Parameters.h"

#include <memory>


class Fractal
{
public:
	typedef std::shared_ptr<Fractal> ptr;

public:
	Fractal();
	~Fractal();

	//virtual void compute(const Parameters& params, Array2D<Color>& out) = 0;
	virtual void compute(const Parameters& params, std::function<void()> callback) = 0;
	virtual void cancelComputation(bool wait = true) {};

	//virtual void addAdvanceListener(QObject* listener);//FractalComputationListener* listener);
	//virtual void addComputationEndsListener(QObject* listener);//FractalComputationListener* listener);

	void setArray(Array2D<Color>& array) { myArray = &array; }

	void setImage(Image::ptr image) { myImage = image; }

	virtual void initialize(const Parameters&) {}
	virtual bool isComputing() = 0;
	virtual void clean() {}

//protected:
//	void dispatchComputationAdvances(int perc);

protected:
//	std::vector<FractalComputationListener*> myListeners;
	Array2D<Color>* myArray; //old

	Image::ptr myImage;

	JobManager myManager;

	//boost::signals2::signal<void(int) > mySig;
};

//#include "FParser\fparser.hh"
class GenericParallelizableFractal : public Fractal
{
public:
	typedef std::map<int, MathParser> ParserById;
public:
	virtual void compute(const Parameters& params, std::function<void()> callback) override;
	virtual Color computePixel(double x, double y, const Parameters& params, ParserById& parserById) = 0;
	void cancelComputation(bool wait) override;
	bool isComputing() override;
	virtual void clean() override;
};
