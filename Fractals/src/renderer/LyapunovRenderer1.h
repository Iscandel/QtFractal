#pragma once
#include "LyapunovBaseRenderer.h"

#include "core/Parameters.h"

class LyapunovRenderer1 :
	public LyapunovBaseRenderer
{
public:
	LyapunovRenderer1(const Parameters& params);
	~LyapunovRenderer1();

	Color computeColor(double lambda) override;

protected:
	const double myLambdaMin;
	const double myLambdaMax;
};

