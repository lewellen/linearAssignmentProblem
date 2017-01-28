#ifndef HUNGARIANMETHODSOLVER_H
#define HUNGARIANMETHODSOLVER_H

#include <list>
#include <utility>

#include "Array2D.h"
#include "ISolver.h"

using std::list;
using std::pair;

class HungarianMethodSolver : public ISolver {
public:
	HungarianMethodSolver();
	~HungarianMethodSolver();

	list<size_t> operator() (const Array2D<double>& M) const; 
};

#endif
