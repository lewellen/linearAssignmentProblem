#ifndef ALTERNATIVEMETHODSOLVER_H
#define ALTERNATIVEMETHODSOLVER_H

#include <list>
#include <utility>

#include "Array2DMask.h"
#include "ISolver.h"

using std::list;
using std::pair;

class AlternativeMethodSolver : public ISolver {
public:
	AlternativeMethodSolver();
	~AlternativeMethodSolver();

	list<size_t> operator() (Array2DMask& M); 
};

#endif

