#include <algorithm>
#include <cmath>

#include "Array2D.h"
#include "Assignment.h"
#include "ISolver.h"
#include "AtRandomSolver.h"

using std::swap;

AtRandomSolver::AtRandomSolver() {

}

AtRandomSolver::~AtRandomSolver() {

}

Assignment AtRandomSolver::operator() (const Array2D<double>& A) const {
	assert(A.getNumRows() == A.getNumCols());
	Assignment assignment(A.getNumRows());

	// O(n) - Strawman solver. Want to show on the approximate solvers just how 
	// good/bad they are relative to picking an assignment at random.

	for(size_t i = 0; i < assignment.size(); ++i) {
		assignment[i] = i;		
	}

	// Fisher-yates shuffle
	for(size_t i = assignment.size() - 1; i >= 1; --i) {
		size_t j = rand() % i;
		swap(assignment[i], assignment[j]);
	}
	
	return assignment;
}

