#include "FractalWindow.h"

#include "FractalJob.h"
#include "Mandelbrot.h"

FractalWindow::FractalWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	myParamsByFractal["Mandelbrot"] = Parameters();
	myCurrentParameters = &myParamsByFractal["Mandelbrot"];
	myCurrentParameters->addInt("sizeX", 800);
	myCurrentParameters->addInt("sizeY", 800);
	myCurrentParameters->addDouble("xmin", -2.);
	myCurrentParameters->addDouble("xmax", 2.);
	myCurrentParameters->addDouble("ymin", -2.);
	myCurrentParameters->addDouble("ymax", 2.);
	myCurrentParameters->addInt("maxIter", 50);

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

	connect(ui.myLabelImage, SIGNAL(signalRightButtonDrawFractal(int, int, int, int)), 
		this, SLOT(rightButtonDrawFractal(int, int, int, int)));

	connect(ui.actionChoose_fractal, SIGNAL(triggered()), this, SLOT(showTypeFractal()));

	connect(ui.actionZoomPlus, SIGNAL(triggered()), this, SLOT(zoomPlus()));
	connect(ui.actionZoomMinus, SIGNAL(triggered()), this, SLOT(zoomMinus()));

	myFractal = std::shared_ptr<Mandelbrot>(new Mandelbrot);
	myProgress = ProgressDialog::ptr(new ProgressDialog);
	myFractal->addAdvanceListener(myProgress.get());

	computeFractal(*myCurrentParameters);
	
}

void FractalWindow::rightButtonDrawFractal(int startX, int startY, int endX, int endY)
{
	double x1 = std::min(startX, endX); double x2 = std::max(startX, endX);
	double y1 = std::min(startY, endY); double y2 = std::max(startY, endY);
	int width = myCurrentParameters->getInt("sizeX", 800);
	int height = myCurrentParameters->getInt("sizeY", 800);
	const double XMIN = myCurrentParameters->getDouble("xmin", -2.);
	const double XMAX = myCurrentParameters->getDouble("xmax", 2.);
	const double YMIN = myCurrentParameters->getDouble("ymin", -2.);
	const double YMAX = myCurrentParameters->getDouble("ymax", 2.);

	//On recalcule les nouvelles coordonnées du repère, en se servant de la taille
	//du rectangle proportionnellement à celle de l'image 
	x1 = XMIN + (x1 / width) * std::abs(XMIN - XMAX);
	x2 = XMIN + (x2 / width) * std::abs(XMIN - XMAX);
	y1 = YMIN + (y1 / height)* std::abs(YMIN - YMAX);
	y2 = YMIN + (y2 / height)* std::abs(YMIN - YMAX);

	myCurrentParameters->addDouble("xmin", x1);
	myCurrentParameters->addDouble("xmax", x2);
	myCurrentParameters->addDouble("ymin", y1);
	myCurrentParameters->addDouble("ymax", y2);

	std::cout << x1 << " " << x2 << " " << y1 << " " << y2 << std::endl;

	myProgress->show();

	computeFractal(*myCurrentParameters);
}

void FractalWindow::computeFractal(const Parameters& params)
{
	int width = myCurrentParameters->getInt("sizeX", 800);
	int height = myCurrentParameters->getInt("sizeY", 600);

	myArray.setSize(width, height);
	myFractal->setArray(myArray);

	std::vector<std::shared_ptr<Job> > jobs;

	std::shared_ptr<Job> job(new FractalJob(myFractal, params, width, height));
	jobs.push_back(job);
	myManager.addJobs(jobs, std::bind(&FractalWindow::computationEnds, this));
	//myManager.join();

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
	QImage image(myArray.getWidth(), myArray.getHeight(), QImage::Format_RGB32);
	for (int i = 0; i < myArray.getWidth(); i++)
	{
		for (int j = 0; j < myArray.getHeight(); j++)
		{
			const Color& col = myArray(i, j);
			image.setPixelColor(i, j, QColor(col.r * 255., col.g * 255., col.b * 255.));
		}
	}
	QPixmap pixmap = QPixmap::fromImage(image);
	ui.myLabelImage->setPixmap(pixmap);
	ui.myLabelImage->adjustSize();
}

void FractalWindow::computationEnds()
{
	myProgress->hide();
	affectImage();
}

void FractalWindow::showTypeFractal()
{
	myTypeFractal.show();
}

void FractalWindow::zoomPlus()
{
	double xmin = myCurrentParameters->getDouble("xmin", -2.);
	double xmax = myCurrentParameters->getDouble("xmax", 2.);
	double ymin = myCurrentParameters->getDouble("ymin", -2.);
	double ymax = myCurrentParameters->getDouble("ymax", 2.);

	double areaWidth = std::abs(xmax - xmin);   //Calcul de la taille de la fenêtre en x
	double newWidth = areaWidth / 2.;    //Longueur à enlever au total
	xmin += newWidth / 2;                   //Calcul de la nouvelle coord en xmin
	xmax -= newWidth / 2;					//Calcul de la nouvelle coord en xmax
	double areaHeight = std::abs(ymax - ymin);   //Calcul de la taille de la fenêtre en y
	double newHeight = areaHeight / 2;    //Longueur à enlever au total
	ymin += newHeight / 2;					//Calcul de la nouvelle coord en ymin
	ymax -= newHeight / 2;					//Calcul de la nouvelle coord en yMax
	
	myCurrentParameters->addDouble("xmin", xmin);
	myCurrentParameters->addDouble("xmax", xmax);
	myCurrentParameters->addDouble("ymin", ymin);
	myCurrentParameters->addDouble("ymax", ymax);

	myProgress->show();

	computeFractal(*myCurrentParameters);
}

void FractalWindow::zoomMinus()
{
	double xmin = myCurrentParameters->getDouble("xmin", -2.);
	double xmax = myCurrentParameters->getDouble("xmax", 2.);
	double ymin = myCurrentParameters->getDouble("ymin", -2.);
	double ymax = myCurrentParameters->getDouble("ymax", 2.);

	double areaWidth = std::abs(xmax - xmin);   //Calcul de la taille de la fenêtre en x
	double newWidth = areaWidth / 2.;    //Longueur à enlever au total
	xmin -= newWidth / 2;                   //Calcul de la nouvelle coord en xmin
	xmax += newWidth / 2;					//Calcul de la nouvelle coord en xmax
	double areaHeight = std::abs(ymax - ymin);   //Calcul de la taille de la fenêtre en y
	double newHeight = areaHeight / 2;    //Longueur à enlever au total
	ymin -= newHeight / 2;					//Calcul de la nouvelle coord en ymin
	ymax += newHeight / 2;					//Calcul de la nouvelle coord en yMax

	myCurrentParameters->addDouble("xmin", xmin);
	myCurrentParameters->addDouble("xmax", xmax);
	myCurrentParameters->addDouble("ymin", ymin);
	myCurrentParameters->addDouble("ymax", ymax);

	myProgress->show();

	computeFractal(*myCurrentParameters);
}

//void FractalWindow::computationAdvances(int perc)
//{
//	//std::cout << perc << std::endl;
//	myProgress->computationAdvances(perc);
//	myProgress->repaint();
//}
