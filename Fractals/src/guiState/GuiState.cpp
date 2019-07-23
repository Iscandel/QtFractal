#include "GuiState.h"

#include "gui/FractalWindow.h"

GuiState::GuiState(FractalWindow* window)
:myWindow(window)
{

}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
GuiState::~GuiState(void)
{

}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void GuiState::setFractalWindow(FractalWindow* window)
{
	myWindow = window;
}