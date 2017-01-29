#include <algorithm>
#include <cassert>
#include <limits>
#include <vector>
#include <utility>

#include "Array2D.h"
#include "ISolver.h"
#include "BruteSolver.h"

using std::swap;
using std::vector;
using std::numeric_limits;
using std::pair;

BruteSolver::BruteSolver() {

}

BruteSolver::~BruteSolver() {

}

vector<size_t> BruteSolver::operator() (const Array2D<double>& M) const {
	assert(M.getNumRows() == M.getNumCols());

	vector<size_t> workers(M.getNumRows());	
	for(size_t i = 0; i < workers.size(); ++i) {
		workers[i] = i;
	}

	double minCost = numeric_limits<double>::infinity();
	vector<size_t> minAssign;

	permutation(workers, workers.size(), M, minCost, minAssign);

	return minAssign;
}

void BruteSolver::permutation(
	vector<size_t>& A, size_t n,
	const Array2D<double>& M, double& minCost, vector<size_t>& minAssign) const {

	// Decided to use Heap's algorithm instead of mine (mine used two linked 
	// lists representing unused objects, the other a permutation being built
	// by the call stack; Heap's uses half the storage and vectors are 
	// contiguous - hence better cache performance - so more preferrable.)

	if( n == 1 ) {
		double cost = 0.0;
		for(size_t i = 0; i < A.size(); ++i) {
			cost += M.getEntry(i, A[i]);
		}

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
