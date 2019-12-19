#pragma once

#include "GuiState.h"

class QAction;
class FractalWindow;

class CliffordState : public GuiState
{
public:
	CliffordState(const Parameters&);
	~CliffordState();

	void init() override;

	void free() override;
protected:
	void onClickGeneralConfig();
	void onClickConfigureFractal();

protected:
	std::unique_ptr<QAction> myActionGeneralConfig;
	std::unique_ptr<QAction> myActionConfigureFractal;
};


