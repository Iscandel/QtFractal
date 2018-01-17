#pragma once

#include <QDialog>
#include "ui_GaussianFilterConfigurationDialog.h"

#include "Parameters.h"

class GaussianFilterConfigurationDialog : public QDialog
{
	Q_OBJECT

public:
	GaussianFilterConfigurationDialog(QWidget *parent, Parameters* params);
	~GaussianFilterConfigurationDialog();

	void onOk();

	void onCancel();

	void setParameters(Parameters* params);

private:
	Ui::GaussianFilterConfigurationDialog ui;

	Parameters* myParams;
};
