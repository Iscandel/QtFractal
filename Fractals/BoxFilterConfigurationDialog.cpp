#include "BoxFilterConfigurationDialog.h"

BoxFilterConfigurationDialog::BoxFilterConfigurationDialog(QWidget *parent, Parameters* params)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.myButtonOk, &QPushButton::clicked, this, &BoxFilterConfigurationDialog::onOk);
	connect(ui.myButtonCancel, &QPushButton::clicked, this, &BoxFilterConfigurationDialog::onCancel);

	setParameters(params);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
BoxFilterConfigurationDialog::~BoxFilterConfigurationDialog()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BoxFilterConfigurationDialog::setParameters(Parameters* params)
{
	myParams = params;
	ui.mySpinRadiusX->setValue(myParams->getDouble("radiusX", 0.5));
	ui.mySpinRadiusY->setValue(myParams->getDouble("radiusY", 0.5));
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BoxFilterConfigurationDialog::onOk()
{
	myParams->addDouble("radiusX", ui.mySpinRadiusX->value());
	myParams->addDouble("radiusY", ui.mySpinRadiusY->value());

	hide();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void BoxFilterConfigurationDialog::onCancel()
{
	hide();
}
