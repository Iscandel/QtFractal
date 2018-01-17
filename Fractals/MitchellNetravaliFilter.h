#pragma once
#include "ReconstructionFilter.h"

///////////////////////////////////////////////////////////////////////////////
/// \brief Filter from Mitchell and Netravali : Reconstruction filter for 
/// computer graphics.
/// Nice looking.
///////////////////////////////////////////////////////////////////////////////
class MitchellNetravaliFilter :
	public ReconstructionFilter
{
public:
	MitchellNetravaliFilter(double radiusX = 2., double radiusY = 2., double B = 0.33, double C = 0.33);
	MitchellNetravaliFilter(const Parameters& params);
	~MitchellNetravaliFilter(void);

	double getValue(double x, double y);

	double func1D(double val);

protected:
	double myB;
	double myC;
};

