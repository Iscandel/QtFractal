//#pragma once
//#include "Array2D.h"
//#include "Color.h"
//#include "FractalComputationListener.h"
//#include "Parameters.h"
//
//#include <vector>
//
//#include <qobject.h>
//
//class Fractal : public QObject
//{
//	Q_OBJECT
//
//public:
//	typedef std::shared_ptr<Fractal> ptr;
//public:
//	Fractal();
//	~Fractal();
//
//	virtual void compute(const Parameters& params, Array2D<Color>& out) = 0;
//
//	void addAdvanceListener(FractalComputationListener* listener);
//
//signals:
//	void emitComputationAdvances(int perc);
//
//protected:
//	void dispatchComputationAdvances(int perc);
//
//protected:
//	std::vector<FractalComputationListener*> myListeners;
//};
//
