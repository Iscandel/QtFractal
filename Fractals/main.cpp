#include "FractalWindow.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets>

//#include "Mandelbrot.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	FractalWindow w;
	w.show();
	return a.exec();
}
