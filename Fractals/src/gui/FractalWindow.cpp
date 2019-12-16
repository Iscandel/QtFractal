#include "FractalWindow.h"

#include "filter/BoxFilter.h"
#include "tools/ImageUtils.h"
//#include "filter/MitchellNetravaliFilter.h"
#include "job/FractalJob.h"
#include "fractal/Mandelbrot.h"
//#include "Julia.h"
//#include "Newton.h"

#include "factory/ObjectFactoryManager.h"

#include <qfiledialog.h>
#include <qerrormessage.h>
#include <QtWidgets/QCheckbox.h>

#include "core/Maths.h"
#include "core/OrthographicCamera.h"
#include "core/ProgressNotifier.h"
#include "tools/Timer.h"

Timer timer;

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

	typedef std::vector<uint8_t> QtType;
	qRegisterMetaType<QtType>("std::vector<uint8_t>");

	myProgressBar = new QProgressBar(ui.statusBar);
	myStatusLabel = new QLabel(ui.statusBar);
	
	ui.statusBar->addWidget(myStatusLabel, 1);
	ui.statusBar->addWidget(myProgressBar, 3);
	Notifier::ptr notifier(new QtUiNotifier);
	//std::cout << notifier.get() << std::endl;
	//std::cout << (QtUiNotifier*)notifier.get() << std::endl;
	connect((QtUiNotifier*)notifier.get(), &QtUiNotifier::signalComputationAdvances, this, &FractalWindow::computationAdvances);
	connect((QtUiNotifier*)notifier.get(), &QtUiNotifier::signalJobsDone, this, &FractalWindow::computationEnds, Qt::QueuedConnection);
	connect((QtUiNotifier*)notifier.get(), &QtUiNotifier::signalReportDataModified, this, &FractalWindow::refreshImage, Qt::QueuedConnection); //queued connection is ok, but copies the vector
	//connect((QtUiNotifier*)notifier.get(), &QtUiNotifier::signalReportDataModified, this, &FractalWindow::refreshImage, Qt::ConnectionType::DirectConnection); //direct connection is ok only if view refresh is then call with emit
	ProgressNotifier::addNotifier(notifier);

	connect(ui.myLabelImage, SIGNAL(signalRightButtonDrawFractal(int, int, int, int, float)), 
		this, SLOT(rightButtonDrawFractal(int, int, int, int, float)));

	connect(ui.actionChoose_fractal, SIGNAL(triggered()), this, SLOT(showTypeFractal()));

	connect(ui.actionZoomPlus, SIGNAL(triggered()), this, SLOT(zoomPlus()));
	connect(ui.actionZoomMinus, SIGNAL(triggered()), this, SLOT(zoomMinus()));

	connect(ui.actionTrace_fractal, SIGNAL(triggered()), this, SLOT(traceFractal()));
	connect(ui.actionSave_image, SIGNAL(triggered()), this, SLOT(saveFractal()));

	//connect(this, SIGNAL(aboutToQuit()), this, SLOT(cleanApp()));
	bool res = connect(ui.actionStop, SIGNAL(triggered()), this, SLOT(cancelComputation()));

	myProgress = ProgressDialog::ptr(new ProgressDialog);

	
	//QCheckBox* checkDragMode = new QCheckBox(ui.statusBar);
	//ui.mainToolBar->addWidget(checkDragMode);
	connect(ui.actionDrag_mode, SIGNAL(toggled(bool)), this, SLOT(changeDragMode()));

	myCamera = std::make_shared<OrthographicCamera>();
	real scaleX = 2.;
	real scaleY = 2.;
	Transform transform;
	Eigen::Vector2d scale(scaleX, scaleY);
	Eigen::Rotation2D<real> rot;
	Eigen::Vector2d translation;
	transform.fromPositionOrientationScale(translation, rot, scale);
	myCurrentParameters.addTransform("toWorld", transform);
	//myCurrentParameters.addDouble("scaleX", scaleX);
	//myCurrentParameters.addDouble("scaleY", scaleY);

	Eigen::Affine2d affine = Eigen::Affine2d::Identity();
	affine.prescale(Eigen::Vector2d(scaleX, scaleY));
	myCamera->setWorldTransform(affine);

	computeFractal(myCurrentParameters);	
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
FractalWindow::~FractalWindow()
{
	//ProgressNotifier::clearNotifiers();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void FractalWindow::addActionToToolbar(QAction* action)
{
	ui.mainToolBar->addAction(action);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void FractalWindow::removeActionFromToolbar(QAction* action)
{
	ui.mainToolBar->removeAction(action);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void FractalWindow::resetParameters()
{
	myOriginParameters = Parameters();
	myCurrentParameters = Parameters();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void FractalWindow::initState(GuiState::ptr state)
{
	state->setFractalWindow(this);
	state->setParameters(&myCurrentParameters);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void FractalWindow::setGuiState(GuiState::ptr state)
{
	//initState(state);
	while (popState());
	pushState(state);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void FractalWindow::pushState(GuiState::ptr state)
{
	initState(state);
	myStates.push_back(state);
	state->init();
}

//=============================================================================
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

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
bool FractalWindow::popState(GuiState::ptr state)
{
	std::vector<GuiState::ptr>::iterator it = myStates.erase(
		std::find(myStates.begin(), myStates.end(), state));

	return !(it == myStates.end());
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
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

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void FractalWindow::rightButtonDrawFractal(int startX, int startY, int endX, int endY, float angle)
{
	double x1 = std::min(startX, endX); double x2 = std::max(startX, endX);
	double y1 = std::min(startY, endY); double y2 = std::max(startY, endY);
	int width = myCurrentParameters.getInt("sizeX", 800);
	int height = myCurrentParameters.getInt("sizeY", 800);
	// double XMIN = myCurrentParameters.getDouble("xmin", -2.);
	// double XMAX = myCurrentParameters.getDouble("xmax", 2.);
	// double YMIN = myCurrentParameters.getDouble("ymin", -2.);
	// double YMAX = myCurrentParameters.getDouble("ymax", 2.);
	// double ANGLE = myCurrentParameters.getDouble("angle", 0.);

	//double sumAngle = myCurrentParameters.getDouble("angle", 0.) + angle;

	//double scaleX = myCurrentParameters.getDouble("scaleX", 2.);
	//double scaleY = myCurrentParameters.getDouble("scaleY", 2.);
	//double cx = myCurrentParameters.getDouble("centerX", 0.);
	//double cy = myCurrentParameters.getDouble("centerY", 0.);
	//Eigen::Vector2d center(cx, cy);


	//Eigen::Affine2d affine = Eigen::Affine2d::Identity();
	//affine.prescale(Eigen::Vector2d(scaleX, scaleY));
	//affine.prerotate(-sumAngle * M_PI / 180.);
	//affine.pretranslate(center);
	//myCamera->setWorldTransform(affine);

	//scaleX *= (x2 - x1) / width;
	//scaleY *= (y2 - y1) / height;
	//myCurrentParameters.addDouble("scaleX", scaleX);
	//myCurrentParameters.addDouble("scaleY", scaleY);

	//double normCenterX = ((x2 + x1) / 2. - width / 2.) / (width / 2.); //[-1 1]
	//double normCenterY = ((y2 + y1) / 2. - height / 2.) / (height / 2.); //[-1 1]
	//auto transformedCenter = affine * Eigen::Vector3d(normCenterX, normCenterY, 1);
	//myCurrentParameters.addDouble("centerX", transformedCenter(0));
	//myCurrentParameters.addDouble("centerY", transformedCenter(1));


	//
	Transform transform = myCurrentParameters.getTransform("toWorld", Transform::Identity());
	Eigen::Matrix2d scale;
	Eigen::Matrix2d mRot;
	
	//transform.computeRotationScaling<Eigen::Matrix2d, Eigen::Vector2d>((Eigen::Matrix2d*)nullptr, (Eigen::Vector2d*)nullptr);
	transform.computeRotationScaling(&mRot, &scale);
	Eigen::Vector2d translation = transform.translation();
	Eigen::Rotation2D<real> rot;
	rot.fromRotationMatrix(mRot);
	rot.angle() -= angle  * M_PI / 180.;
	transform.fromPositionOrientationScale(translation, rot, Eigen::Vector2d(scale.diagonal()));
	std::cout << scale << std::endl;
	std::cout << scale.diagonal() << std::endl;
	
	double normCenterX = ((x2 + x1) / 2. - width / 2.) / (width / 2.); //[-1 1]
	double normCenterY = ((y2 + y1) / 2. - height / 2.) / (height / 2.); //[-1 1]
	auto transformedCenter = transform * Eigen::Vector3d(normCenterX, normCenterY, 1);
	transform.fromPositionOrientationScale(transformedCenter.segment(0,2), rot, Eigen::Vector2d(scale.diagonal()));
	myCurrentParameters.addTransform("toWorld", transform);
	//


	//double centerX = width / 2.;
	//double centerY = height / 2.;
	//double theta = sumAngle * M_PI / 180.;
	//double cosTheta = std::cos(theta);
	//double sinTheta = std::sin(theta);
	//double r00 = cosTheta; double r01 = sinTheta; double r10 = -sinTheta; double r11 = cosTheta;

	//Eigen::Affine2d affine = Eigen::Affine2d::Identity();
	//affine.pretranslate(Eigen::Vector2d(-width/2., -height/2.));
	//affine.prerotate(Eigen::Rotation2D<double>(sumAngle * M_PI / 180.));
	//affine.pretranslate(Eigen::Vector2d((r00 * centerX + r01 * centerY), (r10 * centerX + r11 * centerY)));
	//auto transform = affine;//.inverse();
	//Eigen::Vector3d p1(startX, startY, 1);
	//p1 = transform * p1;
	//Eigen::Vector3d p2(endX, endY, 1);
	//p2 = transform * p2;
	//x1 = std::min(p1.x(), p2.x());y1 = std::min(p1.y(), p2.y());
	//x2 = std::max(p1.x(), p2.x());y2 = std::max(p1.y(), p2.y());

	//Recompute the new frame coordinates using rectangle size according to image size
	//x1 = XMIN + (x1 / width) * std::abs(XMIN - XMAX);
	//x2 = XMIN + (x2 / width) * std::abs(XMIN - XMAX);
	//y1 = YMIN + (y1 / height)* std::abs(YMIN - YMAX);
	//y2 = YMIN + (y2 / height)* std::abs(YMIN - YMAX);


	//double theta = -myCurrentParameters.getDouble("angle", 0.)  * M_PI / 180.;
	//double cosTheta = std::cos(theta);
	//double sinTheta = std::sin(theta);
	//x1 = cosTheta * x1 - sinTheta * y1;
	//y1 = sinTheta * x1 + cosTheta * y1;
	//x2 = cosTheta * x2 - sinTheta * y2;
	//y2 = sinTheta * x2 + cosTheta * y2;
	//if (x2 < x1) std::swap(x1, x2);
	//if (y2 < y1) std::swap(y1, y2);

	//myCurrentParameters.addDouble("xmin", x1);
	//myCurrentParameters.addDouble("xmax", x2);
	//myCurrentParameters.addDouble("ymin", y1);
	//myCurrentParameters.addDouble("ymax", y2);
	//myCurrentParameters.addDouble("angle", sumAngle);

	traceFractal();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void FractalWindow::computeFractal(const Parameters& params)
{
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

	myCamera->setSize(width, height);
	myImage = Image::ptr(new Image(width, height));
	if (myCurrentParameters.getBool("useFilter", false))
	{
		std::string type = myCurrentParameters.getString("filter", "Box") + "Filter";
		auto factory = ObjectFactoryManager<ReconstructionFilter>::getInstance()->getFactory(type);
		auto filter = factory->create(myCurrentParameters);
		myImage->setFilter(filter);
	}
		
	myFractal->setImage(myImage);
	Transform transform = myCurrentParameters.getTransform("toWorld", Transform::Identity());
	myCamera->setWorldTransform(transform);
	myFractal->setCamera(myCamera);
	int minX, maxX, minY, maxY;
	myImage->getTrueImageMinMax(minX, maxX, minY, maxY);

	//if(myRefreshImage.size() != width * height * 4)
	//{
	//	myRefreshImage.clear();	
	//	myRefreshImage.resize(width * height * 4, 0);
	//}
	//myRefreshImage.resize((maxX - minX) * (maxY - minY) * 4, 0);
	if (myRefreshImage.size() != width * height)
	{
		myRefreshImage.clear();
		myRefreshImage.resize(width * height, 0);
	}

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

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void FractalWindow::affectImage()
{
	ui.myLabelImage->setPixmap(QPixmap());
	myImage->postProcessColor();
	Array2D<Pixel>& array = myImage->getPixels();
	int sizeX = myImage->getSizeX();
	int sizeY = myImage->getSizeY();
	int overlapX = myImage->getOverlapX();
	int overlapY = myImage->getOverlapY();
	//std::lock_guard<std::mutex> lock(myRefreshMutex);
	QImage image(array.getWidth(), array.getHeight(), QImage::Format_RGB32);
	//for (int i = 0; i < sizeX; i++)
	//{
	//	for (int j = 0; j < sizeY; j++)
	//	{
	//		//const Color& col = myArray(i, j);
	//		const Pixel& col = array(i + overlapX, j + overlapY);
	//		//if (col.myColor.r > 1. || col.myColor.g > 1. || col.myColor.b > 1.)
	//		//	std::cout << col.myColor << std::endl;
	//		myRefreshImage[(j * sizeX + i) * 4] = (uchar)thresholding<int>(col.myColor.b * 255., 0, 255);
	//		myRefreshImage[(j * sizeX + i) * 4 + 1] = (uchar)thresholding<int>(col.myColor.g * 255., 0, 255);
	//		myRefreshImage[(j * sizeX + i) * 4 + 2] = (uchar)thresholding<int>(col.myColor.r * 255., 0, 255);
	//		myRefreshImage[(j * sizeX + i) * 4 + 3] = (uchar)0xff;
	//		image.setPixelColor(i, j, QColor(thresholding<int>(col.myColor.r * 255., 0, 255), 
	//										 thresholding<int>(col.myColor.g * 255., 0, 255), 
	//										 thresholding<int>(col.myColor.b * 255., 0, 255)));
	//	}
	//}

	ImageUtils::convert(array, overlapX, overlapY, sizeX, sizeY, myRefreshImage, ImageUtils::RGB32);
	image = QImage((uchar*)myRefreshImage.data(), sizeX, sizeY, sizeX * ImageUtils::bytesPerPixelFromFormat(ImageUtils::RGB32), QImage::Format_RGB32);

	QPixmap pixmap = QPixmap::fromImage(image);
	//pixmap.detach();
	ui.myLabelImage->setPixmap(pixmap);
	ui.myLabelImage->adjustSize();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void FractalWindow::computationEnds()
{
	std::cout << timer.elapsedTime() << std::endl;
	
	if (!myFractal->isComputing())
	{
		myProgressBar->hide();
		myStatusLabel->hide();
		affectImage();
	}
	myProgress->hide();
	//affectImage();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void FractalWindow::showTypeFractal()
{
	myTypeFractal.show();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void FractalWindow::zoomPlus()
{
	//double scaleX = myCurrentParameters.getDouble("scaleX", 2.);
	//double scaleY = myCurrentParameters.getDouble("scaleY", 2.);
	//myCurrentParameters.addDouble("scaleX", scaleX / 2.);
	//myCurrentParameters.addDouble("scaleY", scaleY / 2.);

	Transform transform = myCurrentParameters.getTransform("toWorld", Transform::Identity());
	Eigen::Matrix2d scale;
	Eigen::Matrix2d mRot;

	transform.computeRotationScaling(&mRot, &scale);
	Eigen::Vector2d translation = transform.translation();
	Eigen::Rotation2D<real> rot;
	rot.fromRotationMatrix(mRot);
	transform.fromPositionOrientationScale(translation, rot,Eigen::Vector2d(scale.diagonal()) / 2.);
	myCurrentParameters.addTransform("toWorld", transform);

	//double xmin = myCurrentParameters.getDouble("xmin", -2.);
	//double xmax = myCurrentParameters.getDouble("xmax", 2.);
	//double ymin = myCurrentParameters.getDouble("ymin", -2.);
	//double ymax = myCurrentParameters.getDouble("ymax", 2.);

	//double areaWidth = std::abs(xmax - xmin);   //Window size X
	//double newWidth = areaWidth / 2.;    //New window size X
	//xmin += newWidth / 2;                   //New xmin
	//xmax -= newWidth / 2;					//New xmax
	//double areaHeight = std::abs(ymax - ymin);   //Window size Y
	//double newHeight = areaHeight / 2;    //New window size X
	//ymin += newHeight / 2;					
	//ymax -= newHeight / 2;					
	//
	//myCurrentParameters.addDouble("xmin", xmin);
	//myCurrentParameters.addDouble("xmax", xmax);
	//myCurrentParameters.addDouble("ymin", ymin);
	//myCurrentParameters.addDouble("ymax", ymax);

	traceFractal();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void FractalWindow::zoomMinus()
{
	//double scaleX = myCurrentParameters.getDouble("scaleX", 2.);
	//double scaleY = myCurrentParameters.getDouble("scaleY", 2.);
	//myCurrentParameters.addDouble("scaleX", scaleX * 2.);
	//myCurrentParameters.addDouble("scaleY", scaleY * 2.);

	Transform transform = myCurrentParameters.getTransform("toWorld", Transform::Identity());
	Eigen::Matrix2d scale;
	Eigen::Matrix2d mRot;
	
	transform.computeRotationScaling(&mRot, &scale);
	Eigen::Vector2d translation = transform.translation();
	Eigen::Rotation2D<real> rot;rot.fromRotationMatrix(mRot);
	transform.fromPositionOrientationScale(translation, rot, Eigen::Vector2d(scale.diagonal() * 2.));
	myCurrentParameters.addTransform("toWorld", transform);

	//double xmin = myCurrentParameters.getDouble("xmin", -2.);
	//double xmax = myCurrentParameters.getDouble("xmax", 2.);
	//double ymin = myCurrentParameters.getDouble("ymin", -2.);
	//double ymax = myCurrentParameters.getDouble("ymax", 2.);

	//double areaWidth = std::abs(xmax - xmin);   //Window size X
	//double newWidth = areaWidth;    //New window size X
	//xmin -= newWidth / 2;                   //New xmin
	//xmax += newWidth / 2;					//New xmax
	//double areaHeight = std::abs(ymax - ymin);   //Window size Y
	//double newHeight = areaHeight;    //New window size X
	//ymin -= newHeight / 2;					
	//ymax += newHeight / 2;				

	//myCurrentParameters.addDouble("xmin", xmin);
	//myCurrentParameters.addDouble("xmax", xmax);
	//myCurrentParameters.addDouble("ymin", ymin);
	//myCurrentParameters.addDouble("ymax", ymax);

	traceFractal();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void FractalWindow::changeDragMode()
{
	ui.myLabelImage->setDragMode(ui.actionDrag_mode->isChecked());
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void FractalWindow::setFractal(Fractal::ptr fractal)
{
	myFractal = fractal;

	//myFractal->addAdvanceListener(myProgress.get());
	//myFractal->addComputationEndsListener(this);

	//Set filter, image
	//myImage = Image::ptr(new Image(width, height));
	//myImage->setFilter(ReconstructionFilter::ptr(new MitchellNetravaliFilter(2., 2., 0.33, 0.33)));
	//myFractal->setImage(myImage);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void FractalWindow::traceFractal()
{
	timer.reset();
	if (myFractal)
		myFractal->cancelComputation(true);

	ui.myLabelImage->setPixmap(QPixmap());

	myProgressBar->setValue(0);
	myProgressBar->show();
	myStatusLabel->show();
	
	computeFractal(myCurrentParameters);
	
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void FractalWindow::cancelComputation()
{
	myFractal->cancelComputation();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void FractalWindow::saveFractal()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Save image"), "",
		tr("JPG (*.jpg);;PNG (*.png);;JPEG(*.jpeg);;BMP(*.bmp);;All Files (*)"));

	bool saved = ui.myLabelImage->pixmap()->save(fileName, "PNG");

	ILogger::log() << "saved ? " << saved << " " << fileName.toStdString() << "\n";
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void FractalWindow::computationAdvances(const QString& message, float perc)
{
	myStatusLabel->setText(message);
	myProgressBar->setValue(perc);
	myProgressBar->repaint();
}

//void FractalWindow::update()
//{
//
//}
//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void FractalWindow::refreshImage(int minX, int maxX, int minY, int maxY, int overlapX, int overlapY, const std::vector<uint8_t>& vecData)
{
	//ui.myLabelImage->setPixmap(QPixmap());

	int sizeX = myImage->getSizeX();
	int sizeY = myImage->getSizeY();
	//Block size, including borders due to reconstruction filter
//	int blockSize = maxX - minX; 
//
//	if (minX == 0)
//		maxX -= overlapX;
//	else if(maxX >= sizeX)
//		maxX = sizeX;
//	else
//		overlapX = 0;
//	if (minY == 0)
//		maxY -= overlapY;
//	else if(maxY >= sizeY)
//		maxY = sizeY;
//	else
//		overlapY = 0;
//	
////std::lock_guard<std::mutex> lock(myRefreshMutex);
//	const uint8_t* data = vecData.data();
//	int tmpY = 0;
//	for (int y = minY; y < maxY; y++)
//	{
//		int tmpX = 0;
//		for (int x = minX; x < maxX; x++)
//		{	
//			uint32_t argb = Color::toARGB32((uint8_t)0xff,
//				(uint8_t)data[((tmpY + overlapY) * blockSize + (tmpX + overlapX)) * 3],
//				(uint8_t)data[((tmpY + overlapY) * blockSize + (tmpX + overlapX)) * 3 + 1],
//				(uint8_t)data[((tmpY + overlapY) * blockSize + (tmpX + overlapX)) * 3 + 2]);
//			//myRefreshImage[(y * sizeX + x) * 4] = argb;
//			myRefreshImage[(y * sizeX + x) * 4 + 2] = (uchar)data[((tmpY + overlapY) * blockSize + (tmpX + overlapX)) * 3];
//			myRefreshImage[(y * sizeX + x) * 4 + 1] = (uchar)data[((tmpY + overlapY) * blockSize + (tmpX + overlapX)) * 3 + 1];
//			myRefreshImage[(y * sizeX + x) * 4] = (uchar)data[((tmpY + overlapY) * blockSize + (tmpX + overlapX)) * 3 + 2];
//			myRefreshImage[(y * sizeX + x) * 4 + 3] = (uchar)0xff;
//			tmpX++;
//		}
//		tmpY++;
//	}
	
	ImageUtils::convert(vecData, 3, minX, maxX, minY, maxY, overlapX, overlapY, sizeX, sizeY, myRefreshImage, ImageUtils::RGB32);

	QImage image((uchar*)myRefreshImage.data(), sizeX, sizeY, sizeX * 4, QImage::Format_RGB32);
	QPixmap pixmap = QPixmap::fromImage(image);

	//pixmap.detach();
	ui.myLabelImage->setPixmap(pixmap);
	//ui.myLabelImage->adjustSize();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void FractalWindow::cleanApp()
{
	ProgressNotifier::clearNotifiers();
	if (myFractal)
		myFractal->cancelComputation();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void FractalWindow::closeEvent(QCloseEvent *event)
{
	cleanApp();

	QMainWindow::closeEvent(event);
}


//directConnection + emit updateUI