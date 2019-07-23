#pragma once

#include <QDialog>
#include "ui_MandelbrotConfigurationDialog.h"

#include "core/Parameters.h"

class MandelbrotConfigurationDialog : public QDialog
{
	Q_OBJECT

public:
	MandelbrotConfigurationDialog(QWidget *parent = Q_NULLPTR);
	~MandelbrotConfigurationDialog();

	void onOk();
	void onCancel();

	void setParameters(Parameters* params);

protected:
	void onRendererValueChanged(const std::string& value);
	void onClickConfigureRenderer();

private:
	Ui::MandelbrotConfigurationDialog ui;

	Parameters* myParams;
};
