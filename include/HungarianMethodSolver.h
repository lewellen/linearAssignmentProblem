#ifndef HUNGARIANMETHODSOLVER_H
#define HUNGARIANMETHODSOLVER_H

#include <vector>
#include <utility>

#include "Array2D.h"
#include "ISolver.h"

using std::vector;
using std::pair;

class HungarianMethodSolver : public ISolver {
public:
	HungarianMethodSolver();
	~HungarianMethodSolver();

	vector<size_t> operator() (const Array2D<double>& M) const; 
};

#endif
