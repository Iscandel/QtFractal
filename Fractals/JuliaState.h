#pragma once
#include "GuiState.h"

class FractalWindow;

class JuliaState :
	public GuiState
{
public:
	JuliaState(FractalWindow* window = nullptr);
	~JuliaState();

	virtual void init() override;
};