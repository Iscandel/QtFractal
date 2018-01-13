#include "JuliaState.h"

#include "FractalWindow.h"
#include "Julia.h"
#include "ObjectFactoryManager.h"

JuliaState::JuliaState(FractalWindow* window)
	:GuiState(window)
{
}


JuliaState::~JuliaState()
{
}

void JuliaState::init()
{
	//myWindow->setFractal(std::shared_ptr<Fractal>(new Julia));
	myWindow->addParameter("fractal", "Julia");
}

FACTORY_REGISTER_TYPE_WITH_KEY(FractalWindow::getStrFractalName(FractalWindow::JULIA), JuliaState, GuiState)