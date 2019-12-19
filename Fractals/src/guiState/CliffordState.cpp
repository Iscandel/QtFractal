#include "CliffordState.h"

#include "gui/FractalWindow.h"
#include "gui/GeneralConfigurationDialog.h"
#include "fractal/Clifford.h"
#include "factory/ObjectFactoryManager.h"

#include <qaction.h>

CliffordState::CliffordState(const Parameters&)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
CliffordState::~CliffordState()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void CliffordState::init()
{
	myWindow->resetParameters();
	//myWindow->setFractal(std::shared_ptr<Mandelbrot>(new Mandelbrot));
	myWindow->addParameter("fractal", "Clifford");

	myActionConfigureFractal.reset(new QAction);
	myActionConfigureFractal->setObjectName(QStringLiteral("actionConfigureFractal"));
	myActionConfigureFractal->setText(QApplication::translate("CliffordState", "Configure fractal", Q_NULLPTR));
	myWindow->addActionToToolbar(myActionConfigureFractal.get());

	myActionGeneralConfig.reset(new QAction);
	myActionGeneralConfig->setObjectName(QStringLiteral("actionGeneralConfig"));
	myActionGeneralConfig->setText(QApplication::translate("CliffordState", "General configuration", Q_NULLPTR));
	myWindow->addActionToToolbar(myActionGeneralConfig.get());

	//QObject::connect(myActionConfigureFractal.get(), &QAction::triggered, this, &LyapunovState::onClickConfigureFractal);
	//QObject::connect(myActionGeneralConfig.get(), &QAction::triggered, this, &LyapunovState::onClickGeneralConfig);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void CliffordState::free()
{
	myWindow->removeActionFromToolbar(myActionConfigureFractal.get());
	myWindow->removeActionFromToolbar(myActionGeneralConfig.get());

	myActionConfigureFractal.reset();
	myActionGeneralConfig.reset();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void CliffordState::onClickGeneralConfig()
{
	//GeneralConfigurationDialog dlg(myWindow);
	//dlg.setWindowModality(Qt::WindowModality::WindowModal);
	//dlg.setParameters(myParams);
	//dlg->setAttribute(Qt::WA_DeleteOnClose);
	//dlg.exec();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void CliffordState::onClickConfigureFractal()
{
	//LyapunovConfigurationDialog dlg(myWindow);
	//dlg.setWindowModality(Qt::WindowModality::WindowModal);
	//dlg.setParameters(myParams);
	//dlg->setAttribute(Qt::WA_DeleteOnClose);
	//dlg.exec();
}

FACTORY_REGISTER_TYPE_WITH_KEY(ObjectStaticType<Clifford>::get(), CliffordState, GuiState)
