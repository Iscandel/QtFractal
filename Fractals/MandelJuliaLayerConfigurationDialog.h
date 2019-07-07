#pragma once

#include <QDialog>
#include "ui_MandelJuliaLayerConfigurationDialog.h"

class MandelJuliaLayerConfigurationDialog : public QDialog
{
	Q_OBJECT

public:
	MandelJuliaLayerConfigurationDialog(QWidget *parent = Q_NULLPTR);
	~MandelJuliaLayerConfigurationDialog();

private:
	Ui::MandelJuliaLayerConfigurationDialog ui;
};
