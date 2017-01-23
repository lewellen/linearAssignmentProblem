#ifndef BRUTESOLVER_H
#define BRUTESOLVER_H

#include <list>
#include <utility>

#include "CostMatrix.h"
#include "ISolver.h"

using std::list;
using std::pair;

class BruteSolver : public ISolver {
public:
	BruteSolver();
	~BruteSolver();

	list<size_t> operator() (CostMatrix& M); 

private:
	void permutation(
		list<size_t>& A, list<size_t>& B, 
		CostMatrix& M, double& minCost, list<size_t>& minAssign);
};

#endif

