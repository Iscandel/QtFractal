#pragma once

#include <QDialog>
#include "ui_MandelJuliaRandomRendererDialog.h"

#include "Color.h"
#include "Parameters.h"

class MandelJuliaRandomRendererDialog : public QDialog
{
	Q_OBJECT

public:
	MandelJuliaRandomRendererDialog(QWidget *parent, Parameters* params);
	~MandelJuliaRandomRendererDialog();

	void onValueScrollbarsChanged(int value);

	void onOk();
	void onCancel();

	void onRadioChanged(int checked);

	int getIndexSelectedRadio();

	void setPreviewColor(int r, int g, int b);
private:
	Ui::MandelJuliaRandomRendererDialog ui;

	std::vector<Color> myColors;
	//Color myFractalColor;

	Parameters* myParams;
};
