#include "NewtonState.h"

#include "gui/FractalWindow.h"
#include "gui/GeneralConfigurationDialog.h"
#include "factory/ObjectFactoryManager.h"
#include "fractal/Newton.h"

NewtonState::NewtonState(const Parameters&)
:GuiState(nullptr)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
NewtonState::~NewtonState()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void NewtonState::init()
{
	myWindow->resetParameters();
	//myWindow->setFractal(std::shared_ptr<Mandelbrot>(new Mandelbrot));
	myWindow->addParameter("fractal", "Newton");

	myActionConfigureFractal.reset(new QAction);
	myActionConfigureFractal->setObjectName(QStringLiteral("actionConfigureFractal"));
	myActionConfigureFractal->setText(QApplication::translate("NewtonState", "Configure fractal", Q_NULLPTR));
	myWindow->addActionToToolbar(myActionConfigureFractal.get());

	myActionGeneralConfig.reset(new QAction);
	myActionGeneralConfig->setObjectName(QStringLiteral("actionGeneralConfig"));
	myActionGeneralConfig->setText(QApplication::translate("NewtonState", "General configuration", Q_NULLPTR));
	myWindow->addActionToToolbar(myActionGeneralConfig.get());

	QObject::connect(myActionConfigureFractal.get(), &QAction::triggered, this, &NewtonState::onClickConfigureFractal);
	QObject::connect(myActionGeneralConfig.get(), &QAction::triggered, this, &NewtonState::onClickGeneralConfig);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void NewtonState::free()
{
	myWindow->removeActionFromToolbar(myActionConfigureFractal.get());
	myWindow->removeActionFromToolbar(myActionGeneralConfig.get());

	myActionConfigureFractal.reset();
	myActionGeneralConfig.reset();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void NewtonState::onClickGeneralConfig()
{
	GeneralConfigurationDialog dlg(myWindow);
	dlg.setWindowModality(Qt::WindowModality::WindowModal);
	dlg.setParameters(myParams);
	//dlg->setAttribute(Qt::WA_DeleteOnClose);
	dlg.exec();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void NewtonState::onClickConfigureFractal()
{
	//MandelbrotConfigurationDialog dlg(myWindow);
	//dlg.setWindowModality(Qt::WindowModality::WindowModal);
	//dlg.setParameters(myParams);
	////dlg->setAttribute(Qt::WA_DeleteOnClose);
	//dlg.exec();
}

FACTORY_REGISTER_TYPE_WITH_KEY(ObjectStaticType<Newton>::get(), NewtonState, GuiState)