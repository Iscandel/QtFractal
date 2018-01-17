#pragma once

#include <QDialog>
#include "ui_MitchellNetravaliFilterConfigurationDialog.h"

#include "Parameters.h"

class MitchellNetravaliFilterConfigurationDialog : public QDialog
{
	Q_OBJECT

public:
	MitchellNetravaliFilterConfigurationDialog(QWidget *parent, Parameters* params);
	~MitchellNetravaliFilterConfigurationDialog();

	void onOk();

	void onCancel();

	void setParameters(Parameters* params);

private:
	Ui::MitchellNetravaliFilterConfigurationDialog ui;

	Parameters* myParams;
};
