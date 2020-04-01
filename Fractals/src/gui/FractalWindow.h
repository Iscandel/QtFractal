#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Fractals.h"

#include "ChooseFractalWidget.h"
//#include "FractalComputationListener.h"
#include "fractal/Fractal.h"
#include "guiState/GuiState.h"
#include "core/Image.h"
#include "job/JobManager.h"
#include "core/Parameters.h"

#include "ProgressDialog.h"
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <map>

//Macro pour associer une des valeurs d'énum à des chaines de caractères
//#define MYLIST(x)       \
//x(MANDELBROT, "Mandelbrot") \
//x(JULIA,   "Julia") \
//x(BUDDHABROT,   "Buddhabrot") \
//x(LYAPUNOV,   "Lyapunov") \
//x(NEWTON,   "Newton") \
//x(END,  "")
//
//#define USE_FIRST_ELEMENT(x, y)  x,
//#define USE_SECOND_ELEMENT(x, y) y,

class Fractal;

class FractalWindow : public QMainWindow//, public FractalComputationListener
{
	Q_OBJECT

public:
	//enum FractalNames
	//{
	//	MYLIST(USE_FIRST_ELEMENT)
	//};

public:
	FractalWindow(QWidget *parent = Q_NULLPTR);

	~FractalWindow();

	void computeFractal(const Parameters& params);

	void affectImage();

	void computationEnds();

	void setFractal(Fractal::ptr fractal);

	void setGuiState(GuiState::ptr state);
	void pushState(GuiState::ptr state);

	bool popState();

	bool popState(GuiState::ptr state);

	template<class T> 
	void addParameter(const std::string& key, T value) {}

	void addActionToToolbar(QAction* action);
	void removeActionFromToolbar(QAction* action);

	void resetParameters();

	void cleanApp();

public:
	static void initFractalNames();

	//static std::string getStrFractalName(FractalNames name)
	//{
	//	static bool init = false;

	//	if (!init)
	//	{
	//		initFractalNames();
	//		init = true;
	//	}
	//	return myFractalNames[name];
	//}

public:
	//void computationAdvances(int perc) override;
	void computationAdvances(const QString&, float perc);

protected:
	void closeEvent(QCloseEvent *event) override;

public slots:
	void rightButtonDrawFractal(int startX, int startY, int endX, int endY, float angle);

	void showTypeFractal();

	void zoomPlus();

	void zoomMinus();

	void changeDragMode();

	void traceFractal();

	void saveFractal();

	void cancelComputation();

	void refreshImage(int minX, int maxX, int minY, int maxY, int overlapX, int overlapY, const std::vector<uint8_t>& vecData);

protected:
	void initState(GuiState::ptr state);

public:
	static std::vector<std::string> myFractalNames;

private:
	Ui::FractalsClass ui;

	std::map<std::string, Parameters> myParamsByFractal;
	Parameters myOriginParameters;
	Parameters myCurrentParameters;

	Fractal::ptr myFractal;

	ProgressDialog::ptr myProgress;

	QProgressBar* myProgressBar;
	QLabel* myStatusLabel;

	JobManager myManager; //old

	Array2D<Color> myArray; //old

	Image::ptr myImage;
	Camera::ptr myCamera;

	std::vector<GuiState::ptr> myStates;

	ChooseFractalWidget myTypeFractal;

	std::vector<uint32_t> myRefreshImage;

	std::mutex myRefreshMutex;

};

template<>
inline void FractalWindow::addParameter<double>(const std::string& key, double value) {
	myCurrentParameters.addDouble(key, value);
}

template<>
inline void FractalWindow::addParameter<int>(const std::string& key, int value) {
	myCurrentParameters.addInt(key, value);
}

template<>
inline void FractalWindow::addParameter<std::string>(const std::string& key, std::string value) {
	myCurrentParameters.addString(key, value);
}

template<>
inline void FractalWindow::addParameter<const char*>(const std::string& key, const char* value) {
	myCurrentParameters.addString(key, value);
}

#undef USE_FIRST_ELEMENT
#undef USE_SECOND_ELEMENT
