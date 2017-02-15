#include <algorithm>
#include <cassert>
#include <limits>

#include "Array2D.h"
#include "Assignment.h"
#include "BruteSolver.h"
#include "ISolver.h"

using std::swap;
using std::numeric_limits;

BruteSolver::BruteSolver() {

}

BruteSolver::~BruteSolver() {

}

Assignment BruteSolver::operator() (const Array2D<double>& M) const {
	assert(M.getNumRows() == M.getNumCols());

	Assignment workers(M.getNumRows());	
	for(size_t i = 0; i < workers.size(); ++i) {
		workers[i] = i;
	}

	double minCost = numeric_limits<double>::infinity();
	Assignment minAssign(M.getNumRows());

	permutation(workers, workers.size(), M, minCost, minAssign);

	return minAssign;
}

void BruteSolver::permutation(
	Assignment& A, size_t n,
	const Array2D<double>& M, double& minCost, Assignment& minAssign) const {

	// Decided to use Heap's algorithm instead of mine (mine used two linked 
	// lists representing unused objects, the other a permutation being built
	// by the call stack; Heap's uses half the storage and vectors are 
	// contiguous - hence better cache performance - so more preferrable.)

	if( n == 1 ) {
		double cost = A.cost(M);
		if(minCost > cost) {
			minCost = cost;
			minAssign = A;
		}
	} else {
		if(n % 2 == 0) {
			for(size_t i = 0; i < n; ++i) {
				permutation(A, n - 1, M, minCost, minAssign);
				swap(A[i], A[n-1]);
			}
		} else {
			for(size_t i = 0; i < n; ++i) {
				permutation(A, n - 1, M, minCost, minAssign);
				swap(A[0], A[n-1]);
			}
		}
	}
}
