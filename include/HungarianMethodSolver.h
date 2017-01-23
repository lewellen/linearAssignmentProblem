#ifndef HUNGARIANMETHODSOLVER_H
#define HUNGARIANMETHODSOLVER_H

#include <list>
#include <utility>

#include "Array2DMask.h"
#include "ISolver.h"

using std::list;
using std::pair;

class HungarianMethodSolver : public ISolver {
public:
	HungarianMethodSolver();
	~HungarianMethodSolver();

	list<size_t> operator() (Array2DMask& M); 
};

#endif
