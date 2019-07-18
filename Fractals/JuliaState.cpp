#include "JuliaState.h"

#include "FractalWindow.h"
#include "GeneralConfigurationDialog.h"
#include "Julia.h"
#include "ObjectFactoryManager.h"

#include "MandelbrotConfigurationDialog.h"

#include <qaction.h>

JuliaState::JuliaState(const Parameters&)
	:GuiState(nullptr)
{
}


JuliaState::~JuliaState()
{
}

void JuliaState::init()
{
	myWindow->resetParameters();
	//myWindow->setFractal(std::shared_ptr<Mandelbrot>(new Mandelbrot));
	myWindow->addParameter("fractal", "Julia");

	myActionConfigureFractal.reset(new QAction);
	myActionConfigureFractal->setObjectName(QStringLiteral("actionConfigureFractal"));
	myActionConfigureFractal->setText(QApplication::translate("MandelbrotState", "Configure fractal", Q_NULLPTR));
	myWindow->addActionToToolbar(myActionConfigureFractal.get());

	myActionGeneralConfig = new QAction();
	myActionGeneralConfig->setObjectName(QStringLiteral("actionGeneralConfig"));
	myActionGeneralConfig->setText(QApplication::translate("MandelbrotState", "General configuration", Q_NULLPTR));
	myWindow->addActionToToolbar(myActionGeneralConfig);

	QObject::connect(myActionConfigureFractal.get(), &QAction::triggered, this, &JuliaState::onClickConfigureFractal);
	QObject::connect(myActionGeneralConfig, &QAction::triggered, this, &JuliaState::onClickGeneralConfig);
}

void JuliaState::free()
{
	myWindow->removeActionFromToolbar(myActionGeneralConfig);
	delete myActionGeneralConfig;
}

void JuliaState::onClickConfigureFractal()
{
	MandelbrotConfigurationDialog dlg(myWindow);
	dlg.setWindowModality(Qt::WindowModality::WindowModal);
	dlg.setParameters(myParams);
	//dlg->setAttribute(Qt::WA_DeleteOnClose);
	dlg.exec();
}

void JuliaState::onClickGeneralConfig()
{
	GeneralConfigurationDialog dlg = new GeneralConfigurationDialog(myWindow);
	dlg.setWindowModality(Qt::WindowModality::WindowModal);
	dlg.setParameters(myParams);
	//dlg->setAttribute(Qt::WA_DeleteOnClose);
	dlg.exec();

}

FACTORY_REGISTER_TYPE_WITH_KEY(ObjectStaticType<Julia>::get(), JuliaState, GuiState)