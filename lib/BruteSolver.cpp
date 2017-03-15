#include <algorithm>
#include <cassert>
#include <limits>
#include <stack>

#include "Array2D.h"
#include "Assignment.h"
#include "BruteSolver.h"
#include "ISolver.h"

using std::numeric_limits;
using std::stack;
using std::swap;

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

struct StackEntry {
	size_t n;
	size_t i;
	bool first;

	StackEntry(size_t n, size_t i, bool first) {
		this->n = n;
		this->i = i;
		this->first = first;
	}
};

void BruteSolver::permutation(
	Assignment& A, size_t N,
	const Array2D<double>& M, double& minCost, Assignment& minAssign) const {

	// Decided to use Heap's algorithm instead of mine (mine used two linked 
	// lists representing unused objects, the other a permutation being built
	// by the call stack; Heap's uses half the storage and vectors are 
	// contiguous so better locality.)
	//
	// Modified Heap's algorithm to be iterative rather than recursive.

	stack< StackEntry > S;
	S.push( StackEntry(N, 0, true) );

	double costs[M.getNumRows()] { 0.0 };
	double cost = 0;

	for(size_t row = 0; row < M.getNumRows(); ++row) {
		costs[row] = M.getEntry( row, A[row] );
		cost += costs[row];	
	}

	while(!S.empty()) {
		StackEntry& p = S.top();
		if(p.n == 1) {
			if(minCost > cost) {
				minCost = cost;
				minAssign = A;
			}
			S.pop();
		} else {
			if(p.first) {
				p.first = false;
				S.push( StackEntry(p.n - 1, 0, true) );
			} else {
				size_t from = 0;
				if(p.n % 2 == 0) {
					from = p.i;
				}

 				swap(A[from], A[p.n - 1]);

				cost -= costs[from];
				costs[from] = M.getEntry(from, A[from]);
				cost += costs[from];

				cost -= costs[p.n - 1];
				costs[p.n - 1] = M.getEntry(p.n - 1, A[p.n - 1]);
				cost += costs[p.n-1];

				if(++p.i == p.n) {
					S.pop();
				} else {
					S.push( StackEntry(p.n - 1, 0, true) );
				}
			}
		}
	}

	/*
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
	*/
}
