#ifndef BRUTESOLVER_H
#define BRUTESOLVER_H

#include <list>
#include <utility>

#include "Array2D.h"
#include "ISolver.h"

using std::list;
using std::pair;

class BruteSolver : public ISolver {
public:
	BruteSolver();
	~BruteSolver();

	list<size_t> operator() (const Array2D<double>& M) const; 

private:
	void permutation(
		list<size_t>& A, list<size_t>& B, 
		const Array2D<double>& M, double& minCost, list<size_t>& minAssign) const;
};

#endif

