#pragma once
#include "GuiState.h"

class QAction;
class FractalWindow;

class JuliaState :
	public GuiState
{
public:
	JuliaState(const Parameters&);
	~JuliaState();

	void init() override;

	void free() override;
protected:	
	void onClickConfigureFractal();
	void onClickGeneralConfig();

protected:
	QAction* myActionGeneralConfig;
	std::unique_ptr<QAction> myActionConfigureFractal;
};