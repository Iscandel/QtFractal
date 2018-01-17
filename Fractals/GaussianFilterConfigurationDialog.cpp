#include "GaussianFilterConfigurationDialog.h"

GaussianFilterConfigurationDialog::GaussianFilterConfigurationDialog(QWidget *parent, Parameters* params)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.myButtonOk, &QPushButton::clicked, this, &GaussianFilterConfigurationDialog::onOk);
	connect(ui.myButtonCancel, &QPushButton::clicked, this, &GaussianFilterConfigurationDialog::onCancel);

	setParameters(params);
}

GaussianFilterConfigurationDialog::~GaussianFilterConfigurationDialog()
{
}

void GaussianFilterConfigurationDialog::setParameters(Parameters* params)
{
	myParams = params;
	ui.mySpinRadiusX->setValue(myParams->getDouble("radiusX", 0.5));
	ui.mySpinRadiusY->setValue(myParams->getDouble("radiusY", 0.5));
	ui.mySpinA->setValue(myParams->getDouble("alpha", 1 / (2. * 0.5 * 0.5)));
	ui.mySpinW->setValue(myParams->getDouble("omega", ui.mySpinRadiusX->value()));
}

void GaussianFilterConfigurationDialog::onOk()
{
	myParams->addDouble("radiusX", ui.mySpinRadiusX->value());
	myParams->addDouble("radiusY", ui.mySpinRadiusY->value());
	myParams->addDouble("alpha", ui.mySpinA->value());
	myParams->addDouble("omega", ui.mySpinW->value());

	hide();
}

void GaussianFilterConfigurationDialog::onCancel()
{
	hide();
}

