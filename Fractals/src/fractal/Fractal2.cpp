//#include "Fractal.h"
//
//
//
//Fractal::Fractal()
//{
//}
//
//
//Fractal::~Fractal()
//{
//}
//
//void Fractal::addAdvanceListener(FractalComputationListener* listener) 
//{
//	connect(this, SIGNAL(signalComputationAdvances(int)), listener, SLOT(FractalComputationListener::computationAdvances(int)));
//	//myListeners.push_back(listener); 
//}
//
//
//void Fractal::dispatchComputationAdvances(int perc)
//{
//	emit emitComputationAdvances(perc);
//	//for (FractalComputationListener* listener : myListeners)
//	//{
//	//	listener->computationAdvances(perc);
//	//}
//}