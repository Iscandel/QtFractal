#include "LyapunovState.h"

#include "gui/FractalWindow.h"
#include "gui/GeneralConfigurationDialog.h"
#include "gui/LyapunovConfigurationDialog.h"
#include "fractal/Lyapunov.h"
#include "factory/ObjectFactoryManager.h"

#include <qaction.h>

LyapunovState::LyapunovState(const Parameters&)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
LyapunovState::~LyapunovState()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LyapunovState::init()
{
	myWindow->resetParameters();
	//myWindow->setFractal(std::shared_ptr<Mandelbrot>(new Mandelbrot));
	//myWindow->addParameter("fractal", ObjectStaticType<Lyapunov>::get());
	myWindow->addParameter("fractal", Lyapunov::PRACTICAL_NAME);

	myActionConfigureFractal.reset(new QAction);
	myActionConfigureFractal->setObjectName(QStringLiteral("actionConfigureFractal"));
	myActionConfigureFractal->setText(QApplication::translate("LyapunovState", "Configure fractal", Q_NULLPTR));
	myWindow->addActionToToolbar(myActionConfigureFractal.get());

	myActionGeneralConfig.reset(new QAction);
	myActionGeneralConfig->setObjectName(QStringLiteral("actionGeneralConfig"));
	myActionGeneralConfig->setText(QApplication::translate("LyapunovState", "General configuration", Q_NULLPTR));
	myWindow->addActionToToolbar(myActionGeneralConfig.get());

	QObject::connect(myActionConfigureFractal.get(), &QAction::triggered, this, &LyapunovState::onClickConfigureFractal);
	QObject::connect(myActionGeneralConfig.get(), &QAction::triggered, this, &LyapunovState::onClickGeneralConfig);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LyapunovState::free()
{
	myWindow->removeActionFromToolbar(myActionConfigureFractal.get());
	myWindow->removeActionFromToolbar(myActionGeneralConfig.get());

	myActionConfigureFractal.reset();
	myActionGeneralConfig.reset();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LyapunovState::onClickGeneralConfig()
{
	GeneralConfigurationDialog dlg(myWindow);
	dlg.setWindowModality(Qt::WindowModality::WindowModal);
	dlg.setParameters(myParams);
	//dlg->setAttribute(Qt::WA_DeleteOnClose);
	dlg.exec();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LyapunovState::onClickConfigureFractal()
{
	LyapunovConfigurationDialog dlg(myWindow);
	dlg.setWindowModality(Qt::WindowModality::WindowModal);
	dlg.setParameters(myParams);
	//dlg->setAttribute(Qt::WA_DeleteOnClose);
	dlg.exec();
}

//FACTORY_REGISTER_TYPE_WITH_KEY(ObjectStaticType<Lyapunov>::get(), LyapunovState, GuiState)
FACTORY_REGISTER_TYPE_WITH_KEY(Lyapunov::PRACTICAL_NAME, LyapunovState, GuiState)
