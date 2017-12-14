#include "Fractal.h"

Fractal::Fractal(QObject *parent)
	: QObject(parent)
{
}

Fractal::~Fractal()
{
}

void Fractal::addAdvanceListener(QObject* listener)//FractalComputationListener* listener)
{
	connect(this, SIGNAL(signalComputationAdvances(int)), listener, SLOT(computationAdvances(int)));
	//myListeners.push_back(listener); 
}

//void Fractal::addAdvanceListener2(ProgressDialog& obj)//FractalComputationListener* listener)
//{
//	mySig.connect(boost::bind(&ProgressDialog::computationAdvances, &obj, _1));
//}


void Fractal::dispatchComputationAdvances(int perc)
{
	emit signalComputationAdvances(perc);
	//for (FractalComputationListener* listener : myListeners)
	//{
	//	listener->computationAdvances(perc);
	//}
}