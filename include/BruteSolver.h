#ifndef BRUTESOLVER_H
#define BRUTESOLVER_H

#include <vector>
#include <utility>

#include "Array2D.h"
#include "ISolver.h"

using std::vector;
using std::pair;

class BruteSolver : public ISolver {
public:
	BruteSolver();
	~BruteSolver();

	vector<size_t> operator() (const Array2D<double>& M) const; 

private:
	void permutation(
		vector<size_t>& A, size_t n, 
		const Array2D<double>& M, double& minCost, vector<size_t>& minAssign) const;
};

#endif

