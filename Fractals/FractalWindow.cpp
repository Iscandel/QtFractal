#include "FractalWindow.h"

#include "BoxFilter.h"
#include "MitchellNetravaliFilter.h"
#include "FractalJob.h"
#include "Mandelbrot.h"
#include "Julia.h"
#include "Newton.h"

#include "ObjectFactoryManager.h"

#include <qfiledialog.h>
#include <qerrormessage.h>


#include "ProgressNotifier.h"
#include "tools/Timer.h"

#include <qpixmapcache.h>


Timer timer;

template<class T>
T thresholding(T val, T min, T max)
{
	return val < min ? min : val  > max ? max : val;
}

std::vector<std::string> FractalWindow::myFractalNames;

FractalWindow::FractalWindow(QWidget *parent)
	: QMainWindow(parent)
	//,myTypeFractal(this)
{
	ILogger::setLogger(new ConsoleLog(std::cout));	

	initFractalNames();

	ui.setupUi(this);

	myTypeFractal.setFractalWindow(this);
	myTypeFractal.setFractalNames(myFractalNames);

	//myParamsByFractal["Mandelbrot"] = Parameters();
	//myCurrentParameters = &myParamsByFractal["Mandelbrot"];
	myCurrentParameters.addInt("sizeX", 800);
	myCurrentParameters.addInt("sizeY", 800);
	myCurrentParameters.addDouble("xmin", -2.);
	myCurrentParameters.addDouble("xmax", 2.);
	myCurrentParameters.addDouble("ymin", -2.);
	myCurrentParameters.addDouble("ymax", 2.);
	myCurrentParameters.addInt("maxIter", 50);

	//Mandelbrot frac;
	//Array2D<Color> out;
	//out.setSize(myCurrentParameters->getInt("sizeX", 800), myCurrentParameters->getInt("sizeY", 800));
	//frac.compute(Parameters(), out);
	//
	//QImage image(out.getWidth(), out.getHeight(), QImage::Format_RGB32);
	//for (int i = 0; i < out.getWidth(); i++)
	//{
	//	for (int j = 0; j < out.getHeight(); j++)
	//	{
	//		const Color& col = out(i, j);
	//		image.setPixelColor(i, j, QColor(col.r * 255., col.g * 255., col.b * 255.));
	//	}
	//}
	//QPixmap pixmap = QPixmap::fromImage(image);
	//ui.myLabelImage->setPixmap(pixmap);
	//ui.myLabelImage->adjustSize();


	//ui.myLabelImage->setGeometry(QRect(0, 0, out.getWidth(), out.getHeight()));
	//ui.myLabelImage->setMinimumSize(out.getWidth(), out.getHeight());
	QErrorMessage::qtHandler();

	//typedef const std::vector<uint8_t> QtType;
	//Q_DECLARE_METATYPE(Combination)
	//qRegisterMetaType<Combination>("Combination");
	typedef std::vector<uint8_t> QtType;
	qRegisterMetaType<QtType>("std::vector<uint8_t>");

	myProgressBar = new QProgressBar(ui.statusBar);
	myStatusLabel = new QLabel(ui.statusBar);
	
	ui.statusBar->addWidget(myStatusLabel, 1);
	ui.statusBar->addWidget(myProgressBar, 3);
	Notifier::ptr notifier(new QtUiNotifier);
	std::cout << notifier.get() << std::endl;
	std::cout << (QtUiNotifier*)notifier.get() << std::endl;
	connect((QtUiNotifier*)notifier.get(), &QtUiNotifier::signalComputationAdvances, this, &FractalWindow::computationAdvances);
	connect((QtUiNotifier*)notifier.get(), &QtUiNotifier::signalJobsDone, this, &FractalWindow::computationEnds, Qt::QueuedConnection);
	connect((QtUiNotifier*)notifier.get(), &QtUiNotifier::signalReportDataModified, this, &FractalWindow::refreshImage, Qt::QueuedConnection); //queued connection is ok, but copies the vector
	//connect((QtUiNotifier*)notifier.get(), &QtUiNotifier::signalReportDataModified, this, &FractalWindow::refreshImage, Qt::ConnectionType::DirectConnection); //direct connection is ok only if view refresh is then call with emit
	ProgressNotifier::addNotifier(notifier);

	connect(ui.myLabelImage, SIGNAL(signalRightButtonDrawFractal(int, int, int, int)), 
		this, SLOT(rightButtonDrawFractal(int, int, int, int)));

	connect(ui.actionChoose_fractal, SIGNAL(triggered()), this, SLOT(showTypeFractal()));

	connect(ui.actionZoomPlus, SIGNAL(triggered()), this, SLOT(zoomPlus()));
	connect(ui.actionZoomMinus, SIGNAL(triggered()), this, SLOT(zoomMinus()));

	connect(ui.actionTrace_fractal, SIGNAL(triggered()), this, SLOT(traceFractal()));
	connect(ui.actionSave_image, SIGNAL(triggered()), this, SLOT(saveFractal()));

	//connect(this, SIGNAL(aboutToQuit()), this, SLOT(cleanApp()));
	bool res = connect(ui.actionStop, SIGNAL(triggered()), this, SLOT(cancelComputation()));

	//myFractal = std::shared_ptr<Fractal>(new Julia);
	myProgress = ProgressDialog::ptr(new ProgressDialog);
	//myFractal->addAdvanceListener(myProgress.get());
	//myFractal->addComputationEndsListener(this);
	//std::vector<QtUiNotifier2::ptr> p;
	//QtUiNotifier2::ptr notifier2(new QtUiNotifier2);
	//p.push_back(std::move(notifier2));
	//p.clear();
	//std::unique_ptr<Notifier> p2(new QtUiNotifier2);
	//p.clearNotifiers();
	//myProgress->show();
	computeFractal(myCurrentParameters);	
}

FractalWindow::~FractalWindow()
{
	//ProgressNotifier::clearNotifiers();
}

void FractalWindow::addActionToToolbar(QAction* action)
{
	ui.mainToolBar->addAction(action);
}

void FractalWindow::removeActionFromToolbar(QAction* action)
{
	ui.mainToolBar->removeAction(action);
}

void FractalWindow::resetParameters()
{
	myOriginParameters = Parameters();
	myCurrentParameters = Parameters();
}

void FractalWindow::initState(GuiState::ptr state)
{
	state->setFractalWindow(this);
	state->setParameters(&myCurrentParameters);
}

void FractalWindow::setGuiState(GuiState::ptr state)
{
	//initState(state);
	while (popState());
	pushState(state);
}

///////////////////////////////////////////////////////////////////////////////
// Ajoute un nouvel état de jeu par dessus le précédent (intérêt dans le cas
// d'un menu qui apparait en jeu. Le jeu est dessiné derrière, soit 2 états
// affichés, mais seul le premier capte les évènements
///////////////////////////////////////////////////////////////////////////////
void FractalWindow::pushState(GuiState::ptr state)
{
	initState(state);
	myStates.push_back(state);
	state->init();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
bool FractalWindow::popState()
{
	if (myStates.size() != 0)
	{
		myStates.back()->free();
		myStates.pop_back();

		return true;
	}

	return false;
}

bool FractalWindow::popState(GuiState::ptr state)
{
	std::vector<GuiState::ptr>::iterator it = myStates.erase(
		std::find(myStates.begin(), myStates.end(), state));

	return !(it == myStates.end());
}

void FractalWindow::initFractalNames()
{
	if (myFractalNames.size() != 0)
		return;

#define USE_FIRST_ELEMENT(x, y)  x,
#define USE_SECOND_ELEMENT(x, y) y,

	const char *STRING[] =
	{
		MYLIST(USE_SECOND_ELEMENT)
	};

	auto vec = ObjectFactoryManager<Fractal>::getInstance()->getFactoryList();
	for (auto factory : vec)
		myFractalNames.push_back(factory->getObjectType());

	//for (int i = 0; i < FractalNames::END; i++)
	//{
	//	myFractalNames.push_back(STRING[i]);
	//}
	
}

void FractalWindow::rightButtonDrawFractal(int startX, int startY, int endX, int endY)
{
	double x1 = std::min(startX, endX); double x2 = std::max(startX, endX);
	double y1 = std::min(startY, endY); double y2 = std::max(startY, endY);
	int width = myCurrentParameters.getInt("sizeX", 800);
	int height = myCurrentParameters.getInt("sizeY", 800);
	const double XMIN = myCurrentParameters.getDouble("xmin", -2.);
	const double XMAX = myCurrentParameters.getDouble("xmax", 2.);
	const double YMIN = myCurrentParameters.getDouble("ymin", -2.);
	const double YMAX = myCurrentParameters.getDouble("ymax", 2.);

	//On recalcule les nouvelles coordonnées du repère, en se servant de la taille
	//du rectangle proportionnellement à celle de l'image 
	x1 = XMIN + (x1 / width) * std::abs(XMIN - XMAX);
	x2 = XMIN + (x2 / width) * std::abs(XMIN - XMAX);
	y1 = YMIN + (y1 / height)* std::abs(YMIN - YMAX);
	y2 = YMIN + (y2 / height)* std::abs(YMIN - YMAX);

	myCurrentParameters.addDouble("xmin", x1);
	myCurrentParameters.addDouble("xmax", x2);
	myCurrentParameters.addDouble("ymin", y1);
	myCurrentParameters.addDouble("ymax", y2);

	std::cout << x1 << " " << x2 << " " << y1 << " " << y2 << std::endl;

	//myProgress->show();

	traceFractal();
}

void FractalWindow::computeFractal(const Parameters& params)
{
	//To do
	//if (myFractal->isComputing())
	//	myFractal->cancelComputation(true);
	std::string fractal = myCurrentParameters.getString("fractal", "Mandelbrot");
	auto factory = ObjectFactoryManager<Fractal>::getInstance()->getFactory(fractal);
	setFractal(factory->create(params));

	int width = myCurrentParameters.getInt("sizeX", 800);
	int height = myCurrentParameters.getInt("sizeY", 800);

	//old
	//myArray.setSize(width, height);
	//myFractal->setArray(myArray);

	myImage = Image::ptr(new Image(width, height));
	if (myCurrentParameters.getBool("useFilter", false))
	{
		std::string type = myCurrentParameters.getString("filter", "Box") + "Filter";
		auto factory = ObjectFactoryManager<ReconstructionFilter>::getInstance()->getFactory(type);
		auto filter = factory->create(myCurrentParameters);
		myImage->setFilter(filter);
	}
		
	myFractal->setImage(myImage);
	int minX, maxX, minY, maxY;
	myImage->getTrueImageMinMax(minX, maxX, minY, maxY);

	if(myRefreshImage.size() != width * height * 4)
	{
		myRefreshImage.clear();	
		myRefreshImage.resize(width * height * 4, 0);
	}
	//myRefreshImage.resize((maxX - minX) * (maxY - minY) * 4, 0);

	myFractal->compute(params, std::bind(&FractalWindow::computationEnds, this));
	
	//old
	//std::vector<std::shared_ptr<Job> > jobs;

	//std::shared_ptr<Job> job(new FractalJob(myFractal, params, width, height));
	//jobs.push_back(job);
	//myManager.addJobs(jobs, std::bind(&FractalWindow::computationEnds, this));
	//myManager.join(); //was commented


	//old
	//Mandelbrot frac;
	//Array2D<Color> out;
	//out.setSize(width, height);
	//frac.compute(params, out);

	//QImage image(out.getWidth(), out.getHeight(), QImage::Format_RGB32);
	//for (int i = 0; i < out.getWidth(); i++)
	//{
	//	for (int j = 0; j < out.getHeight(); j++)
	//	{
	//		const Color& col = out(i, j);
	//		image.setPixelColor(i, j, QColor(col.r * 255., col.g * 255., col.b * 255.));
	//	}
	//}
	//QPixmap pixmap = QPixmap::fromImage(image);
	//ui.myLabelImage->setPixmap(pixmap);
	//ui.myLabelImage->adjustSize();
}

void FractalWindow::affectImage()
{
	std::cout << "affect" << std::endl;

	ui.myLabelImage->setPixmap(QPixmap());
	myImage->postProcessColor();
	Array2D<Pixel>& array = myImage->getPixels();
	int sizeX = myImage->getSizeX();
	int sizeY = myImage->getSizeY();
	int overlapX = myImage->getOverlapX();
	int overlapY = myImage->getOverlapY();
	//std::lock_guard<std::mutex> lock(myRefreshMutex);
	QImage image(array.getWidth(), array.getHeight(), QImage::Format_RGB32);
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			//const Color& col = myArray(i, j);
			const Pixel& col = array(i + overlapX, j + overlapY);
			//if (col.myColor.r > 1. || col.myColor.g > 1. || col.myColor.b > 1.)
			//	std::cout << col.myColor << std::endl;
			myRefreshImage[(j * sizeX + i) * 4] = (uchar)thresholding<int>(col.myColor.b * 255., 0, 255);
			myRefreshImage[(j * sizeX + i) * 4 + 1] = (uchar)thresholding<int>(col.myColor.g * 255., 0, 255);
			myRefreshImage[(j * sizeX + i) * 4 + 2] = (uchar)thresholding<int>(col.myColor.r * 255., 0, 255);
			myRefreshImage[(j * sizeX + i) * 4 + 3] = (uchar)0xff;
			image.setPixelColor(i, j, QColor(thresholding<int>(col.myColor.r * 255., 0, 255), 
											 thresholding<int>(col.myColor.g * 255., 0, 255), 
											 thresholding<int>(col.myColor.b * 255., 0, 255)));
		}
	}


	image = QImage( myRefreshImage.data(), sizeX, sizeY, sizeX * 4, QImage::Format_RGB32);

	QPixmap pixmap = QPixmap::fromImage(image);
	//pixmap.detach();
	ui.myLabelImage->setPixmap(pixmap);
	ui.myLabelImage->adjustSize();
}

void FractalWindow::computationEnds()
{
	std::cout << timer.elapsedTime() << std::endl;
	std::cout << "fini" << std::endl;
	if (!myFractal->isComputing())
	{
		myProgressBar->hide();
		myStatusLabel->hide();
		affectImage();
	}
	myProgress->hide();
	//affectImage();
}

void FractalWindow::showTypeFractal()
{
	myTypeFractal.show();
}

void FractalWindow::zoomPlus()
{
	double xmin = myCurrentParameters.getDouble("xmin", -2.);
	double xmax = myCurrentParameters.getDouble("xmax", 2.);
	double ymin = myCurrentParameters.getDouble("ymin", -2.);
	double ymax = myCurrentParameters.getDouble("ymax", 2.);

	double areaWidth = std::abs(xmax - xmin);   //Window size X
	double newWidth = areaWidth / 2.;    //New window size X
	xmin += newWidth / 2;                   //New xmin
	xmax -= newWidth / 2;					//New xmax
	double areaHeight = std::abs(ymax - ymin);   //Window size Y
	double newHeight = areaHeight / 2;    //New window size X
	ymin += newHeight / 2;					
	ymax -= newHeight / 2;					
	
	myCurrentParameters.addDouble("xmin", xmin);
	myCurrentParameters.addDouble("xmax", xmax);
	myCurrentParameters.addDouble("ymin", ymin);
	myCurrentParameters.addDouble("ymax", ymax);

	//myProgress->show();

	traceFractal();
}

void FractalWindow::zoomMinus()
{
	double xmin = myCurrentParameters.getDouble("xmin", -2.);
	double xmax = myCurrentParameters.getDouble("xmax", 2.);
	double ymin = myCurrentParameters.getDouble("ymin", -2.);
	double ymax = myCurrentParameters.getDouble("ymax", 2.);

	double areaWidth = std::abs(xmax - xmin);   //Calcul de la taille de la fenêtre en x
	double newWidth = areaWidth;    //Longueur à enlever au total
	xmin -= newWidth / 2;                   //Calcul de la nouvelle coord en xmin
	xmax += newWidth / 2;					//Calcul de la nouvelle coord en xmax
	double areaHeight = std::abs(ymax - ymin);   //Calcul de la taille de la fenêtre en y
	double newHeight = areaHeight;    //Longueur à enlever au total
	ymin -= newHeight / 2;					//Calcul de la nouvelle coord en ymin
	ymax += newHeight / 2;					//Calcul de la nouvelle coord en yMax

	myCurrentParameters.addDouble("xmin", xmin);
	myCurrentParameters.addDouble("xmax", xmax);
	myCurrentParameters.addDouble("ymin", ymin);
	myCurrentParameters.addDouble("ymax", ymax);

	//myProgress->show();

	traceFractal();
}

void FractalWindow::setFractal(Fractal::ptr fractal)
{
	myFractal = fractal;

	myFractal->addAdvanceListener(myProgress.get());
	myFractal->addComputationEndsListener(this);

	//Set filter, image
	//myImage = Image::ptr(new Image(width, height));
	//myImage->setFilter(ReconstructionFilter::ptr(new MitchellNetravaliFilter(2., 2., 0.33, 0.33)));
	//myFractal->setImage(myImage);
}

void FractalWindow::traceFractal()
{
	timer.reset();
	if (myFractal)
		myFractal->cancelComputation(true);

	ui.myLabelImage->setPixmap(QPixmap());

	myProgressBar->setValue(0);
	myProgressBar->show();
	myStatusLabel->show();
	
	//myProgress->resetProgressBar();
	//myProgress->show();
	computeFractal(myCurrentParameters);
	
}

void FractalWindow::cancelComputation()
{
	myFractal->cancelComputation();
}

void FractalWindow::saveFractal()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Save image"), "",
		tr("JPG (*.jpg);;PNG (*.png);;JPEG(*.jpeg);;BMP(*.bmp);;All Files (*)"));

	bool saved = ui.myLabelImage->pixmap()->save(fileName, "PNG");

	ILogger::log() << "saved ? " << saved << " " << fileName.toStdString() << "\n";
}

void FractalWindow::computationAdvances(const QString& message, float perc)
{
	myStatusLabel->setText(message);
	myProgressBar->setValue(perc);
	myProgressBar->repaint();

	//myProgress->computationAdvances(perc);
	//myProgress->repaint();
}

//void FractalWindow::update()
//{
//
//}
void FractalWindow::refreshImage(int minX, int maxX, int minY, int maxY, int overlapX, int overlapY, const std::vector<uint8_t>& vecData)
{
	//ui.myLabelImage->setPixmap(QPixmap());

	int sizeX = myImage->getSizeX();
	int sizeY = myImage->getSizeY();
	//Block size, including borders due to reconstruction filter
	int blockSize = maxX - minX; 

	if (minX == 0)
		maxX -= overlapX;
	else if(maxX >= sizeX)
		maxX = sizeX;
	else
		overlapX = 0;
	if (minY == 0)
		maxY -= overlapY;
	else if(maxY >= sizeY)
		maxY = sizeY;
	else
		overlapY = 0;
	
//std::lock_guard<std::mutex> lock(myRefreshMutex);
	const uint8_t* data = vecData.data();
	int tmpY = 0;
	for (int y = minY; y < maxY; y++)
	{
		int tmpX = 0;
		for (int x = minX; x < maxX; x++)
		{	
			myRefreshImage[(y * sizeX + x) * 4 + 2] = (uchar)data[((tmpY + overlapY) * blockSize + (tmpX + overlapX)) * 3];
			myRefreshImage[(y * sizeX + x) * 4 + 1] = (uchar)data[((tmpY + overlapY) * blockSize + (tmpX + overlapX)) * 3 + 1];
			myRefreshImage[(y * sizeX + x) * 4] = (uchar)data[((tmpY + overlapY) * blockSize + (tmpX + overlapX)) * 3 + 2];
			myRefreshImage[(y * sizeX + x) * 4 + 3] = (uchar)0xff;
			tmpX++;
		}
		tmpY++;
	}
	
	QImage image(myRefreshImage.data(), sizeX, sizeY, sizeX * 4, QImage::Format_RGB32);
	QPixmap pixmap = QPixmap::fromImage(image);

	//pixmap.detach();
	ui.myLabelImage->setPixmap(pixmap);
	//ui.myLabelImage->adjustSize();
}

void FractalWindow::cleanApp()
{
	ProgressNotifier::clearNotifiers();
	if (myFractal)
		myFractal->cancelComputation();
}

void FractalWindow::closeEvent(QCloseEvent *event)
{
	cleanApp();
	//ProgressNotifier::clearNotifiers();
	QMainWindow::closeEvent(event);
}


//cancelComputation -> supprimer job done si pas de job qui étaient en cours
//affect image à remettre
//directConnection + emit updateUI