#ifndef IMINIMIZEOBJECTIVE_H
#define IMINIMIZEOBJECTIVE_H

#include "Array2D.h"
#include "IObjective.h"

class MinimizeObjective : public IObjective {
public:
	MinimizeObjective();
	~MinimizeObjective();

	void operator() (Array2D<double>& M) const;
};

#endif
