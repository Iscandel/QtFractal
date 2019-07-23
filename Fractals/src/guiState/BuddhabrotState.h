#pragma once
#include "GuiState.h"

#include <memory>

class QAction;
class FractalWindow;

class BuddhabrotState :
	public GuiState
{
public:
	BuddhabrotState(const Parameters&);
	~BuddhabrotState();

	void init() override;

	void free() override;
protected:
	void onClickGeneralConfig();
	void onClickConfigureFractal();

protected:
	std::unique_ptr<QAction> myActionGeneralConfig;
	std::unique_ptr<QAction> myActionConfigureFractal;
};

