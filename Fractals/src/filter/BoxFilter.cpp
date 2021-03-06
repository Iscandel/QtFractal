#include "BoxFilter.h"

#include "factory/ObjectFactoryManager.h"


BoxFilter::BoxFilter(double radiusX, double radiusY)
:ReconstructionFilter(radiusX, radiusY)
{
	precompute();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
BoxFilter::BoxFilter(const Parameters& params)
: ReconstructionFilter(params)
{
	precompute();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
BoxFilter::~BoxFilter(void)
{
}

FACTORY_REGISTER_TYPE(BoxFilter, ReconstructionFilter)