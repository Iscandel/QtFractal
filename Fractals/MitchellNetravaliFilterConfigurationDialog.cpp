#include "MitchellNetravaliFilterConfigurationDialog.h"

MitchellNetravaliFilterConfigurationDialog::MitchellNetravaliFilterConfigurationDialog(QWidget *parent, Parameters* params)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.myButtonOk, &QPushButton::clicked, this, &MitchellNetravaliFilterConfigurationDialog::onOk);
	connect(ui.myButtonCancel, &QPushButton::clicked, this, &MitchellNetravaliFilterConfigurationDialog::onCancel);

	setParameters(params);
}

MitchellNetravaliFilterConfigurationDialog::~MitchellNetravaliFilterConfigurationDialog()
{
}

void MitchellNetravaliFilterConfigurationDialog::setParameters(Parameters* params)
{
	myParams = params;
	ui.mySpinRadiusX->setValue(myParams->getDouble("radiusX", 0.5));
	ui.mySpinRadiusY->setValue(myParams->getDouble("radiusY", 0.5));
	ui.mySpinB->setValue(myParams->getDouble("B", 0.33));
	ui.mySpinC->setValue(myParams->getDouble("C", 0.33));
}

void MitchellNetravaliFilterConfigurationDialog::onOk()
{
	myParams->addDouble("radiusX", ui.mySpinRadiusX->value());
	myParams->addDouble("radiusY", ui.mySpinRadiusY->value());
	myParams->addDouble("B", ui.mySpinB->value());
	myParams->addDouble("C", ui.mySpinC->value());

	hide();
}

void MitchellNetravaliFilterConfigurationDialog::onCancel()
{
	hide();
}