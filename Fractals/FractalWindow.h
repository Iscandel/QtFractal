#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Fractals.h"

#include "ChooseFractalWidget.h"
#include "FractalComputationListener.h"
#include "Fractal.h"
#include "JobManager.h"
#include "Parameters.h"

#include "ProgressDialog.h"

#include <map>



class Fractal;

class FractalWindow : public QMainWindow//, public FractalComputationListener
{
	Q_OBJECT

public:
	FractalWindow(QWidget *parent = Q_NULLPTR);

	void computeFractal(const Parameters& params);

	void affectImage();

	void computationEnds();

public:
	//void computationAdvances(int perc) override;

public slots:
	void rightButtonDrawFractal(int startX, int startY, int endX, int endY);

	void showTypeFractal();

	void zoomPlus();

	void zoomMinus();

private:
	Ui::FractalsClass ui;

	std::map<std::string, Parameters> myParamsByFractal;
	Parameters myGeneralParameters;
	Parameters* myCurrentParameters;

	Fractal::ptr myFractal;

	ProgressDialog::ptr myProgress;

	JobManager myManager;

	Array2D<Color> myArray;

	ChooseFractalWidget myTypeFractal;

};
