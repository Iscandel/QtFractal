#pragma once
#include "Fractal.h"
class Buddhabrot :
	public Fractal
{
public:
	Buddhabrot();
	~Buddhabrot();

	Color computePixel(double a, double b, const Parameters& params);
	bool escapesToInfinity(double a, double b, bool passage2, int composante);

protected:
	double XMIN;
	double XMAX;
	double YMIN;
	double YMAX;
};

