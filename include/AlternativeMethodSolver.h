#ifndef ALTERNATIVEMETHODSOLVER_H
#define ALTERNATIVEMETHODSOLVER_H

#include <utility>

#include "Array2D.h"
#include "Assignment.h"
#include "ISolver.h"

class AlternativeMethodSolver : public ISolver {
public:
	AlternativeMethodSolver();
	~AlternativeMethodSolver();

	Assignment operator() (const Array2D<double>& M) const;
};

#endif

