#include "MandelbrotState.h"

#include "FractalWindow.h"
#include "Mandelbrot.h"
#include "ObjectFactoryManager.h"

MandelbrotState::MandelbrotState(FractalWindow* window)
:GuiState(window)
{
}


MandelbrotState::~MandelbrotState()
{
}

void MandelbrotState::init()
{
	myWindow->setFractal(std::shared_ptr<Mandelbrot>(new Mandelbrot));
	myWindow->addParameter("fractal", "Mandelbrot");
}

FACTORY_REGISTER_TYPE_WITH_KEY(FractalWindow::getStrFractalName(FractalWindow::MANDELBROT), MandelbrotState, GuiState)