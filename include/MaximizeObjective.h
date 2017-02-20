#ifndef IMAXIMIZEOBJECTIVE_H
#define IMAXIMIZEOBJECTIVE_H

#include "Array2D.h"
#include "IObjective.h"

class MaximizeObjective : public IObjective {
public:
	MaximizeObjective();
	~MaximizeObjective();

	void operator() (Array2D<double>& M) const;
};

#endif
