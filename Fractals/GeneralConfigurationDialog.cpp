#include "GeneralConfigurationDialog.h"
#include "BoxFilterConfigurationDialog.h"
#include "MitchellNetravaliFilterConfigurationDialog.h"
#include "GaussianFilterConfigurationDialog.h"

#include <iostream>

GeneralConfigurationDialog::GeneralConfigurationDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.myButtonOk, &QPushButton::clicked, this, &GeneralConfigurationDialog::onOk);
	connect(ui.myButtonCancel, &QPushButton::clicked, this, &GeneralConfigurationDialog::onCancel);
	connect(ui.mySpinOversampling, 
			static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), 
			this, 
			&GeneralConfigurationDialog::onOverSamplingValueChanged);
	connect(ui.myButtonConfigFilter, &QPushButton::clicked, this, &GeneralConfigurationDialog::onConfigure);
}

GeneralConfigurationDialog::~GeneralConfigurationDialog()
{
	std::cout << "boum" << std::endl;
}

void GeneralConfigurationDialog::setParameters(Parameters* params) 
{ 
	myParams = params; 
	ui.mySpinNbThreads->setValue(myParams->getInt("threadNumber", 1));
	ui.mySpinOversampling->setValue(myParams->getInt("oversampling", 1));
	ui.mySpinBlockSize->setValue(myParams->getInt("blockSize", 32));
	ui.myCheckboxUseFilter->setChecked(myParams->getBool("useFilter", false));
	ui.myComboFilterType->setCurrentText(myParams->getString("filter", "Box").c_str());
}

void GeneralConfigurationDialog::onOk()
{
	myParams->addInt("threadNumber", ui.mySpinNbThreads->value());
	myParams->addInt("oversampling", ui.mySpinOversampling->value());
	myParams->addInt("blockSize", ui.mySpinBlockSize->value());
	myParams->addBool("useFilter", ui.myCheckboxUseFilter->isChecked());
	if (ui.myCheckboxUseFilter->isChecked())
	{
		myParams->addString("filter", ui.myComboFilterType->currentText().toStdString());
	}

	hide();
}

void GeneralConfigurationDialog::onCancel()
{
	hide();
}

void GeneralConfigurationDialog::onOverSamplingValueChanged(int value)
{
	if (value > 1)
	{
		ui.myCheckboxUseFilter->setChecked(true);
		ui.myCheckboxUseFilter->setEnabled(false);
	}
	else
	{
		ui.myCheckboxUseFilter->setEnabled(true);
	}
}

void GeneralConfigurationDialog::onConfigure()
{
	if(ui.myComboFilterType->currentText() == "Box")
	{
		BoxFilterConfigurationDialog dlg(this, myParams);
		dlg.setWindowModality(Qt::WindowModality::WindowModal);
		//dlg->setAttribute(Qt::WA_DeleteOnClose);
		dlg.exec();
	}
	else if(ui.myComboFilterType->currentText() == "MitchellNetravali")
	{
		MitchellNetravaliFilterConfigurationDialog dlg(this, myParams);
		dlg.setWindowModality(Qt::WindowModality::WindowModal);
		//dlg->setAttribute(Qt::WA_DeleteOnClose);
		dlg.exec();
	}
	else if (ui.myComboFilterType->currentText() == "Gaussian")
	{
		GaussianFilterConfigurationDialog dlg(this, myParams);
		dlg.setWindowModality(Qt::WindowModality::WindowModal);
		//dlg->setAttribute(Qt::WA_DeleteOnClose);
		dlg.exec();
	}
}