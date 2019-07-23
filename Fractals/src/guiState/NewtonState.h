#pragma once
#include "GuiState.h"

class QAction;
class FractalWindow;

class NewtonState :
	public GuiState
{
public:
	NewtonState(const Parameters&);
	~NewtonState();

	void init() override;

	void free() override;
protected:
	void onClickGeneralConfig();
	void onClickConfigureFractal();

protected:
	std::unique_ptr<QAction> myActionGeneralConfig;
	std::unique_ptr<QAction> myActionConfigureFractal;
};

