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

	Transform defaultTransform;
	defaultTransform.setScale((real)2., (real)2.);
	auto transform = myParams->getTransform("toWorld", defaultTransform);
	auto scale = transform.getScale();
	auto center = transform.getTranslation();

	//ie, defaultMin * scaleX + centerX -> -1 * scaleX + centerX
	//Or apply transform to min, but then it takes into account rotation
	ui.mySpinXMin->setValue(center.x() - scale.x());//myParams->getDouble("xmin", -2.));
	ui.mySpinYMin->setValue(center.y() - scale.y());//myParams->getDouble("ymin", -2.));
	ui.mySpinXMax->setValue(center.x() + scale.x());//myParams->getDouble("xmax", 2.));
	ui.mySpinYMax->setValue(center.y() + scale.y());//myParams->getDouble("ymax", 2.));

	//ui.mySpinXMin->setValue(myParams->getDouble("xmin", -2.));
	//ui.mySpinYMin->setValue(myParams->getDouble("ymin", -2.));
	//ui.mySpinXMax->setValue(myParams->getDouble("xmax", 2.));
	//ui.mySpinYMax->setValue(myParams->getDouble("ymax", 2.));
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
	Transform transform;
	transform.setScale(Point2r((ui.mySpinXMax->value() - ui.mySpinXMin->value()) / 2.,
		(ui.mySpinYMax->value() - ui.mySpinYMin->value()) / 2.));
	transform.setTranslation((ui.mySpinXMax->value() + ui.mySpinXMin->value()) / 2.,
		(ui.mySpinYMax->value() + ui.mySpinYMin->value()) / 2.);
	myParams->addTransform("toWorld", transform);

	//myParams->addDouble("xmin", ui.mySpinXMin->value());
	//myParams->addDouble("ymin", ui.mySpinYMin->value());
	//myParams->addDouble("xmax", ui.mySpinXMax->value());
	//myParams->addDouble("ymax", ui.mySpinYMax->value());
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
