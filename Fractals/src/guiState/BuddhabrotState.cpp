#include "BuddhabrotState.h"


#include "gui/FractalWindow.h"
#include "gui/GeneralConfigurationDialog.h"
#include "gui/BuddhabrotConfigurationDialog.h"
#include "fractal/Buddhabrot.h"
#include "factory/ObjectFactoryManager.h"

#include <qaction.h>

BuddhabrotState::BuddhabrotState(const Parameters&)
:GuiState(nullptr)
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
BuddhabrotState::~BuddhabrotState()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BuddhabrotState::init()
{
	myWindow->resetParameters();
	//myWindow->setFractal(std::shared_ptr<Mandelbrot>(new Mandelbrot));
	//myWindow->addParameter("fractal", ObjectStaticType<Buddhabrot>::get());//FractalWindow::getStrFractalName(FractalWindow::BUDDHABROT));
	myWindow->addParameter("fractal", Buddhabrot::PRACTICAL_NAME);

	//Notifier::ptr notifier(new QtUiNotifier("Buddhabrot"));

	//myWindow->connect((QtUiNotifier*)notifier.get(), &QtUiNotifier::signalJobsDone, myWindow, &FractalWindow::computationEnds, Qt::DirectConnection);

	//ProgressNotifier::addNotifier(notifier);
	//ProgressNotifier::moveToFront(notifier->getName());

	myActionConfigureFractal.reset(new QAction);
	myActionConfigureFractal->setObjectName(QStringLiteral("actionConfigureFractal"));
	myActionConfigureFractal->setText(QApplication::translate("BuddhabrotState", "Configure fractal", Q_NULLPTR));
	myWindow->addActionToToolbar(myActionConfigureFractal.get());

	myActionGeneralConfig.reset(new QAction);
	myActionGeneralConfig->setObjectName(QStringLiteral("actionGeneralConfig"));
	myActionGeneralConfig->setText(QApplication::translate("BuddhabrotState", "General configuration", Q_NULLPTR));
	myWindow->addActionToToolbar(myActionGeneralConfig.get());

	QObject::connect(myActionConfigureFractal.get(), &QAction::triggered, this, &BuddhabrotState::onClickConfigureFractal);
	QObject::connect(myActionGeneralConfig.get(), &QAction::triggered, this, &BuddhabrotState::onClickGeneralConfig);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BuddhabrotState::free()
{
	myWindow->removeActionFromToolbar(myActionConfigureFractal.get());
	myWindow->removeActionFromToolbar(myActionGeneralConfig.get());

	myActionConfigureFractal.reset();
	myActionGeneralConfig.reset();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BuddhabrotState::onClickGeneralConfig()
{
	GeneralConfigurationDialog dlg(myWindow);
	dlg.setWindowModality(Qt::WindowModality::WindowModal);
	dlg.setParameters(myParams);
	//dlg->setAttribute(Qt::WA_DeleteOnClose);
	dlg.exec();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BuddhabrotState::onClickConfigureFractal()
{
	BuddhabrotConfigurationDialog dlg(myWindow);
	dlg.setWindowModality(Qt::WindowModality::WindowModal);
	dlg.setParameters(myParams);
	//dlg->setAttribute(Qt::WA_DeleteOnClose);
	dlg.exec();
}

//FACTORY_REGISTER_TYPE_WITH_KEY(FractalWindow::getStrFractalName(FractalWindow::BUDDHABROT), BuddhabrotState, GuiState)
//FACTORY_REGISTER_TYPE_WITH_KEY(ObjectStaticType<Buddhabrot>::get(), BuddhabrotState, GuiState)
FACTORY_REGISTER_TYPE_WITH_KEY(Buddhabrot::PRACTICAL_NAME, BuddhabrotState, GuiState)