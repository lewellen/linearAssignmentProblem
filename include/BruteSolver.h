#ifndef BRUTESOLVER_H
#define BRUTESOLVER_H

#include <list>
#include <utility>

#include "Array2DMask.h"
#include "ISolver.h"

using std::list;
using std::pair;

class BruteSolver : public ISolver {
public:
	BruteSolver();
	~BruteSolver();

	list<size_t> operator() (Array2DMask& M); 

private:
	void permutation(
		list<size_t>& A, list<size_t>& B, 
		Array2DMask& M, double& minCost, list<size_t>& minAssign);
};

#endif

