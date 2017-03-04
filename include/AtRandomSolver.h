#ifndef ATRANDOMSOLVER_H
#define ATRANDOMSOLVER_H

#include <utility>

#include "Array2D.h"
#include "Assignment.h"
#include "ISolver.h"

class AtRandomSolver : public ISolver {
public:
	AtRandomSolver();
	~AtRandomSolver();

	Assignment operator() (const Array2D<double>& M) const;
};

#endif

