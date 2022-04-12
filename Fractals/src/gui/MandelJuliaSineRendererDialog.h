#pragma once

#include <QDialog>
#include "ui_MandelJuliaSineRendererDialog.h"

#include "core/Parameters.h"

class MandelJuliaSineRendererDialog : public QDialog
{
	Q_OBJECT

public:
	MandelJuliaSineRendererDialog(QWidget *parent, Parameters* params);
	~MandelJuliaSineRendererDialog();

	void onOk();
	void onCancel();

	void setParameters(Parameters* params);

	void onRadioChanged(int checked);

	int getIndexSelectedRadio();

	void setPreviewColor(int r, int g, int b);


	std::vector<Color> myColors;
	//Color myFractalColor;

protected:
	void initGUIElementVector(QDoubleSpinBox* element, const std::string& key, const std::vector<std::any>& default, int index);

private:
	Ui::MandelJuliaSineRendererDialog ui;
	Parameters* myParams;
};
