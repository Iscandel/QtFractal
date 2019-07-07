#pragma once

#include <QDialog>
#include "ui_LyapunovConfigurationDialog.h"

#include "Parameters.h"

class LyapunovConfigurationDialog : public QDialog
{
	Q_OBJECT

public:
	LyapunovConfigurationDialog(QWidget *parent = Q_NULLPTR);
	~LyapunovConfigurationDialog();

	void onOk();
	void onCancel();

	void onClickConfigureRenderer();
	void setParameters(Parameters* params);

private:
	Ui::LyapunovConigurationDialog ui;

	Parameters* myParams;
};
