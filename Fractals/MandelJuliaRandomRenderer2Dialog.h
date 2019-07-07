#pragma once

#include <QDialog>
#include "ui_MandelJuliaRandomRenderer2Dialog.h"

#include "Parameters.h"
#include "Rng.h"

class MandelJuliaRandomRenderer2Dialog : public QDialog
{
	Q_OBJECT

public:
	MandelJuliaRandomRenderer2Dialog(QWidget *parent, Parameters* params);
	~MandelJuliaRandomRenderer2Dialog();

	void setParameters(Parameters* params);

protected:
	void onOk();
	void onCancel();
	void onRandom();
	void onAddColor();
	void onDeleteColor();
	void onMoveUp();
	void onMoveDown();
	void onChangeFractalColor();
	void setPreviewColor(int r, int g, int b);

private:
	Ui::MandelJuliaRandomRenderer2Dialog ui;

	Parameters* myParams;

	Rng myRng;

	Color myFractalColor;
};
