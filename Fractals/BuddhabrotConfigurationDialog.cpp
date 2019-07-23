#include "BuddhabrotConfigurationDialog.h"

BuddhabrotConfigurationDialog::BuddhabrotConfigurationDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.myButtonOk, &QPushButton::clicked, this, &BuddhabrotConfigurationDialog::onOk);
	connect(ui.myButtonCancel, &QPushButton::clicked, this, &BuddhabrotConfigurationDialog::onCancel);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
BuddhabrotConfigurationDialog::~BuddhabrotConfigurationDialog()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BuddhabrotConfigurationDialog::setParameters(Parameters* params)
{
	myParams = params;
	ui.mySpinXMin->setValue(myParams->getDouble("xmin", -2.));
	ui.mySpinYMin->setValue(myParams->getDouble("ymin", -2.));
	ui.mySpinXMax->setValue(myParams->getDouble("xmax", 2.));
	ui.mySpinYMax->setValue(myParams->getDouble("ymax", 2.));
	ui.mySpinSizeX->setValue(myParams->getInt("sizeX", 800));
	ui.mySpinSizeY->setValue(myParams->getInt("sizeY", 800));
	ui.mySpinIterationsRed->setValue(myParams->getInt("maxIterRed", 50));
	ui.mySpinIterationsGreen->setValue(myParams->getInt("maxIterGreen", 50));
	ui.mySpinIterationsBlue->setValue(myParams->getInt("maxIterBlue", 50));
	ui.mySpinLightIntensity->setValue(myParams->getDouble("lightIntensity", 2.3));

}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BuddhabrotConfigurationDialog::onOk()
{
	myParams->addDouble("xmin", ui.mySpinXMin->value());
	myParams->addDouble("ymin", ui.mySpinYMin->value());
	myParams->addDouble("xmax", ui.mySpinXMax->value());
	myParams->addDouble("ymax", ui.mySpinYMax->value());
	myParams->addInt("sizeX", ui.mySpinSizeX->value());
	myParams->addInt("sizeY", ui.mySpinSizeY->value());
	myParams->addInt("maxIterRed", ui.mySpinIterationsRed->value());
	myParams->addInt("maxIterGreen", ui.mySpinIterationsGreen->value());
	myParams->addInt("maxIterBlue", ui.mySpinIterationsBlue->value());
	myParams->addDouble("lightIntensity", ui.mySpinLightIntensity->value());


	hide();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BuddhabrotConfigurationDialog::onCancel()
{
	hide();
}
