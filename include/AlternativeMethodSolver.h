#ifndef ALTERNATIVEMETHODSOLVER_H
#define ALTERNATIVEMETHODSOLVER_H

#include <list>
#include <utility>

#include "CostMatrix.h"
#include "ISolver.h"

using std::list;
using std::pair;

class AlternativeMethodSolver : public ISolver {
public:
	AlternativeMethodSolver();
	~AlternativeMethodSolver();

	list<size_t> operator() (CostMatrix& M); 
};

#endif

