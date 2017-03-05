#ifndef NAIVEGREEDYSOLVER_H
#define NAIVEGREEDYSOLVER_H

#include "Array2D.h"
#include "Assignment.h"
#include "GreedySolver.h"

class NaiveGreedySolver : public GreedySolver {
public:
	NaiveGreedySolver();
	~NaiveGreedySolver();

	Assignment operator() (const Array2D<double>& M) const;
};

#endif

