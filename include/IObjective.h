#ifndef IOBJECTIVE_H
#define IOBJECTIVE_H

#include "Array2D.h"

class IObjective {
public:
	IObjective();
	virtual ~IObjective();

	virtual void operator() (Array2D<double>& M) const = 0;
};

#endif
