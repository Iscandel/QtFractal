#include "MandelbrotState.h"

#include "FractalWindow.h"
#include "GeneralConfigurationDialog.h"
#include "MandelbrotConfigurationDialog.h"
#include "Mandelbrot.h"
#include "ObjectFactoryManager.h"

#include <qaction.h>

MandelbrotState::MandelbrotState(const Parameters&)
:GuiState(nullptr)
{
}


MandelbrotState::~MandelbrotState()
{
}

void MandelbrotState::init()
{
	myWindow->resetParameters();
	//myWindow->setFractal(std::shared_ptr<Mandelbrot>(new Mandelbrot));
	myWindow->addParameter("fractal", "Mandelbrot");

	myActionConfigureFractal.reset(new QAction);
	myActionConfigureFractal->setObjectName(QStringLiteral("actionConfigureFractal"));
	myActionConfigureFractal->setText(QApplication::translate("MandelbrotState", "Configure fractal", Q_NULLPTR));
	myWindow->addActionToToolbar(myActionConfigureFractal.get());
	
	myActionGeneralConfig.reset(new QAction);
	myActionGeneralConfig->setObjectName(QStringLiteral("actionGeneralConfig"));
	myActionGeneralConfig->setText(QApplication::translate("MandelbrotState", "General configuration", Q_NULLPTR));
	myWindow->addActionToToolbar(myActionGeneralConfig.get());

	QObject::connect(myActionConfigureFractal.get(), &QAction::triggered, this, &MandelbrotState::onClickConfigureFractal);
	QObject::connect(myActionGeneralConfig.get(), &QAction::triggered, this, &MandelbrotState::onClickGeneralConfig);
}

void MandelbrotState::free()
{
	myWindow->removeActionFromToolbar(myActionConfigureFractal.get());
	myWindow->removeActionFromToolbar(myActionGeneralConfig.get());
	
	myActionConfigureFractal.reset();
	myActionGeneralConfig.reset();
}

void MandelbrotState::onClickGeneralConfig()
{
	GeneralConfigurationDialog dlg(myWindow);
	dlg.setWindowModality(Qt::WindowModality::WindowModal);
	dlg.setParameters(myParams);
	//dlg->setAttribute(Qt::WA_DeleteOnClose);
	dlg.exec();
}

void MandelbrotState::onClickConfigureFractal()
{
	MandelbrotConfigurationDialog dlg(myWindow);
	dlg.setWindowModality(Qt::WindowModality::WindowModal);
	dlg.setParameters(myParams);
	//dlg->setAttribute(Qt::WA_DeleteOnClose);
	dlg.exec();
}

FACTORY_REGISTER_TYPE_WITH_KEY(FractalWindow::getStrFractalName(FractalWindow::MANDELBROT), MandelbrotState, GuiState)