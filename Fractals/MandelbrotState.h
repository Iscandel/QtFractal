#pragma once
#include "GuiState.h"

class FractalWindow;

class MandelbrotState :
	public GuiState
{
public:
	MandelbrotState(FractalWindow* window = nullptr);
	~MandelbrotState();

	virtual void init() override;
};

