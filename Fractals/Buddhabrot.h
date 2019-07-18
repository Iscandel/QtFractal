#pragma once
#include "Fractal.h"

#include "Parameters.h"

struct TraceSample
{
	TraceSample(double _x, double _y) :x(_x), y(_y) {}
	double x;
	double y;
};

class Buddhabrot :
	public Fractal
{
public:
	Buddhabrot(const Parameters& params);
	~Buddhabrot();

	void compute(const Parameters& params, std::function<void()> callback) override;

	//vector of components, containing the vector of traces for each component
	std::vector<std::vector<TraceSample>> computePixel(double a, double b, const Parameters& params);

	bool escapesToInfinity(double a, double b, bool passage2, int composante, std::vector<std::vector<TraceSample>>& trace);

	void addComputationEndsListener(QObject* listener) override;

	void postProcessing();

	bool isComputing() override;

protected:
	int myCurrentMaxIt;
	int myMaxItRed;
	int myMaxItGreen;
	int myMaxItBlue;
	int myRefreshFrequency;
	double XMIN;
	double XMAX;
	double YMIN;
	double YMAX;
	std::string myRenderer;
	int myWidth;
	int myHeight;
	double myLightIntensity;

	std::shared_ptr<Image> myImageRed;
	std::shared_ptr<Image> myImageGreen;
	std::shared_ptr<Image> myImageBlue;
};

