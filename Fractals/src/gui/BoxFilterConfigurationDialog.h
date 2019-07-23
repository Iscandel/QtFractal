#pragma once

#include <QDialog>
#include "ui_BoxFilterConfigurationDialog.h"

#include "core/Parameters.h"

class BoxFilterConfigurationDialog : public QDialog
{
	Q_OBJECT

public:
	BoxFilterConfigurationDialog(QWidget *parent, Parameters* params);
	~BoxFilterConfigurationDialog();

	void onOk();

	void onCancel();

	void setParameters(Parameters* params);

private:
	Ui::BoxFilterConfigurationDialog ui;

	Parameters* myParams;
};
