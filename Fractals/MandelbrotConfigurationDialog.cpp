#include "MandelbrotConfigurationDialog.h"

#include "MandelJuliaRandomRendererDialog.h"

MandelbrotConfigurationDialog::MandelbrotConfigurationDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.myButtonOk, &QPushButton::clicked, this, &MandelbrotConfigurationDialog::onOk);
	connect(ui.myButtonCancel, &QPushButton::clicked, this, &MandelbrotConfigurationDialog::onCancel);
	connect(ui.myButtonConfigureRenderer, &QPushButton::clicked, this, &MandelbrotConfigurationDialog::onClickConfigureRenderer);
	//connect(ui.myComboRenderer,
	//	static_cast<void (QComboBox::*)(const QString&)>(&QComboBox::currentTextChanged),
	//	this,
	//	&MandelbrotConfigurationDialog::onRendererValueChanged);
}

MandelbrotConfigurationDialog::~MandelbrotConfigurationDialog()
{
}

void MandelbrotConfigurationDialog::setParameters(Parameters* params)
{
	myParams = params;
	ui.mySpinXMin->setValue(myParams->getDouble("xmin", -2.));
	ui.mySpinYMin->setValue(myParams->getDouble("ymin", -2.));
	ui.mySpinXMax->setValue(myParams->getDouble("xmax", 2.));
	ui.mySpinYMax->setValue(myParams->getDouble("ymax", 2.));
	ui.mySpinSizeX->setValue(myParams->getInt("sizeX", 800));
	ui.mySpinSizeY->setValue(myParams->getInt("sizeY", 800));
	ui.mySpinIterations->setValue(myParams->getInt("maxIter", 50));
	ui.myCheckBoxLogLog->setChecked(myParams->getBool("logLog", false));
}

void MandelbrotConfigurationDialog::onOk()
{
	myParams->addDouble("xmin", ui.mySpinXMin->value());
	myParams->addDouble("ymin", ui.mySpinYMin->value());
	myParams->addDouble("xmax", ui.mySpinXMax->value());
	myParams->addDouble("ymax", ui.mySpinYMax->value());
	myParams->addInt("sizeX", ui.mySpinSizeX->value());
	myParams->addInt("sizeY", ui.mySpinSizeY->value());
	myParams->addInt("maxIter", ui.mySpinIterations->value());
	myParams->addBool("logLog", ui.myCheckBoxLogLog->isChecked());
	myParams->addString("renderer", ui.myComboRenderer->currentText().toStdString());

	hide();
}

void MandelbrotConfigurationDialog::onCancel()
{
	hide();
}

void MandelbrotConfigurationDialog::onRendererValueChanged(const std::string& value)
{
	//if(value == "Random")

}	

void MandelbrotConfigurationDialog::onClickConfigureRenderer()
{
	if (ui.myComboRenderer->currentText() == "Random")
	{
		MandelJuliaRandomRendererDialog dlg(this, myParams);
		dlg.setWindowModality(Qt::WindowModality::WindowModal);
		//dlg->setAttribute(Qt::WA_DeleteOnClose);
		dlg.exec();
	}
}