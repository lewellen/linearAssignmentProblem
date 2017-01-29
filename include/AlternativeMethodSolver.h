#ifndef ALTERNATIVEMETHODSOLVER_H
#define ALTERNATIVEMETHODSOLVER_H

#include <vector>
#include <utility>

#include "Array2D.h"
#include "ISolver.h"

using std::vector;
using std::pair;

class AlternativeMethodSolver : public ISolver {
public:
	AlternativeMethodSolver();
	~AlternativeMethodSolver();

	vector<size_t> operator() (const Array2D<double>& M) const;
};

#endif

