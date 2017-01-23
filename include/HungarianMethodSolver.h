#ifndef HUNGARIANMETHODSOLVER_H
#define HUNGARIANMETHODSOLVER_H

#include <list>
#include <utility>

#include "CostMatrix.h"
#include "ISolver.h"

using std::list;
using std::pair;

class HungarianMethodSolver : public ISolver {
public:
	HungarianMethodSolver();
	~HungarianMethodSolver();

	list< pair<size_t, size_t> > operator() (CostMatrix& M); 
};

#endif
