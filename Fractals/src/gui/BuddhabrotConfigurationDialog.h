#pragma once

#include <QDialog>
#include "ui_BuddhabrotConfigurationDialog.h"

#include "core/Parameters.h"

class BuddhabrotConfigurationDialog : public QDialog
{
	Q_OBJECT

public:
	BuddhabrotConfigurationDialog(QWidget *parent = Q_NULLPTR);
	~BuddhabrotConfigurationDialog();

	void onOk();
	void onCancel();

	void setParameters(Parameters* params);

private:
	Ui::BuddhabrotConfigurationDialog ui;

	Parameters* myParams;
};
