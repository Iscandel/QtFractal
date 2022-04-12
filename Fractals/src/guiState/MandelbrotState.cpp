#include "MandelbrotState.h"

#include "gui/FractalWindow.h"
#include "gui/GeneralConfigurationDialog.h"
#include "gui/MandelbrotConfigurationDialog.h"
#include "fractal/Mandelbrot.h"
#include "factory/ObjectFactoryManager.h"

#include <qaction.h>

MandelbrotState::MandelbrotState(const Parameters&)
:GuiState(nullptr)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
MandelbrotState::~MandelbrotState()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void MandelbrotState::init()
{
	myWindow->resetParameters();
	//myWindow->setFractal(std::shared_ptr<Mandelbrot>(new Mandelbrot));
	myWindow->addParameter("fractal", Mandelbrot::PRACTICAL_NAME);

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

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void MandelbrotState::free()
{
	myWindow->removeActionFromToolbar(myActionConfigureFractal.get());
	myWindow->removeActionFromToolbar(myActionGeneralConfig.get());
	
	myActionConfigureFractal.reset();
	myActionGeneralConfig.reset();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void MandelbrotState::onClickGeneralConfig()
{
	GeneralConfigurationDialog dlg(myWindow);
	dlg.setWindowModality(Qt::WindowModality::WindowModal);
	dlg.setParameters(myParams);
	//dlg->setAttribute(Qt::WA_DeleteOnClose);
	dlg.exec();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void MandelbrotState::onClickConfigureFractal()
{
	MandelbrotConfigurationDialog dlg(myWindow);
	dlg.setWindowModality(Qt::WindowModality::WindowModal);
	dlg.setParameters(myParams);
	//dlg->setAttribute(Qt::WA_DeleteOnClose);
	dlg.exec();
}

//getStaticType<Mandelbrot>() is better than Mandelbrot only because it can only work if the fractal type was defined
//Moreover, it is evaluated at compile time, so there is no issues with the class order definition, 
//ie getStaticType<Mandelbrot>() always exist when the macro is called
//FACTORY_REGISTER_TYPE_WITH_KEY(ObjectStaticType<Mandelbrot>::get(), MandelbrotState, GuiState)
FACTORY_REGISTER_TYPE_WITH_KEY(Mandelbrot::PRACTICAL_NAME, MandelbrotState, GuiState)