#include "FractalWindow.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets>

//#include "Mandelbrot.h"

int main(int argc, char *argv[])
{
	try
	{
		QApplication a(argc, argv);

		FractalWindow w;
		w.show();
		return a.exec();
	}
	catch (const std::exception& exc)
	{
		ILogger::log() << exc.what() << "\n";
	}
	catch (...)
	{
		ILogger::log() << "Unknown exception\n";
	}
}
