#pragma once

#include "core/Parameters.h"
#include <QDialog>
#include "ui_GeneralConfigurationDialog.h"

class GeneralConfigurationDialog : public QDialog
{
	Q_OBJECT

public:
	GeneralConfigurationDialog(QWidget *parent = Q_NULLPTR);
	~GeneralConfigurationDialog();

	void onOk();
	void onCancel();

	void onOverSamplingValueChanged(int value);

	void onConfigure();

	void setParameters(Parameters* params);

private:
	Ui::GeneralConfigurationDialog ui;

	Parameters* myParams;
};
