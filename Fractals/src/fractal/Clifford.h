#pragma once
#include "Fractal.h"

#include "core/Parameters.h"


//
#include "core/ProgressNotifier.h"

struct TraceSample
{
	TraceSample(real _x, real _y) :x(_x), y(_y) {}
	real x;
	real y;
};

class Clifford :
	public Fractal
{
	REGISTER_FRACTAL_PRATICAL_NAME(Clifford)
public:
	Clifford(const Parameters& params);
	~Clifford();

	void compute(const Parameters& params, std::function<void()> callback) override;

	//vector of components, containing the vector of traces for each component
	std::vector<TraceSample> computePixel(double a, double b, int maxIt);

	//bool escapesToInfinity(double a, double b, bool passage2, int composante, std::vector<std::vector<TraceSample>>& trace);

	//void addComputationEndsListener(QObject* listener) override;

	//void postProcessing();

	bool isComputing() {
		return false;
	}

protected:
	int myMaxIt;

	double XMIN;
	double XMAX;
	double YMIN;
	double YMAX;
	std::string myRenderer;
	int myWidth;
	int myHeight;
	double myLightIntensity;

	//std::shared_ptr<Image> myImageRed;
	//std::shared_ptr<Image> myImageGreen;
	//std::shared_ptr<Image> myImageBlue;


	//
	ProgressNotifier myProgress;
};

