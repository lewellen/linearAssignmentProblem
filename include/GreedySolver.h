#ifndef GREEDYSOLVER_H
#define GREEDYSOLVER_H

#include <utility>

#include "Array2D.h"
#include "Assignment.h"
#include "ISolver.h"

class GreedySolver : public ISolver {
public:
	GreedySolver();
	~GreedySolver();

	Assignment operator() (const Array2D<double>& M) const;

private:
	Assignment cubicImpl(const Array2D<double>& M) const;
	Assignment quadarithmicImpl(const Array2D<double>& M) const;	
};

#endif

