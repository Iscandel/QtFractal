#include "ChooseFractalWidget.h"

#include "FractalWindow.h"
#include "ObjectFactoryManager.h"

ChooseFractalWidget::ChooseFractalWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.myOkButton, &QPushButton::clicked, this, &ChooseFractalWidget::onOk);
}

ChooseFractalWidget::~ChooseFractalWidget()
{
}

void ChooseFractalWidget::setFractalWindow(FractalWindow* window)
{
	myWindow = window;
}

void ChooseFractalWidget::setFractalNames(const std::vector<std::string> names)
{
	for (std::string name : names)
		ui.myComboBoxFractal->addItem(QString(name.c_str()));
}

void ChooseFractalWidget::onOk()
{
	if (myWindow)
	{
		auto factory = ObjectFactoryManager<GuiState>::getInstance()->getFactory(ui.myComboBoxFractal->currentText().toStdString());
		auto state = factory->create();
		state->setFractalWindow(myWindow);
		myWindow->setGuiState(state);
	}
		
	hide();
}