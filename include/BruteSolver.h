#ifndef BRUTESOLVER_H
#define BRUTESOLVER_H

#include "Array2D.h"
#include "Assignment.h"
#include "ISolver.h"

class BruteSolver : public ISolver {
public:
	BruteSolver();
	~BruteSolver();

	Assignment operator() (const Array2D<double>& M) const; 

private:
	void permutation(
		Assignment& A, size_t n, 
		const Array2D<double>& M, double& minCost, Assignment& minAssign) const;
};

#endif

