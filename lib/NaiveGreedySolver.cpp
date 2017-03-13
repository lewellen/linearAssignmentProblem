#include <cstdlib>
#include <limits>

#include "Array2D.h"
#include "Array2DMask.h"
#include "Assignment.h"
#include "NaiveGreedySolver.h"

using std::numeric_limits;

NaiveGreedySolver::NaiveGreedySolver() {

}

NaiveGreedySolver::~NaiveGreedySolver() {

}

Assignment NaiveGreedySolver::operator() (const Array2D<double>& A) const {
	assert(A.getNumRows() == A.getNumCols());

	// As written this is O(n^3), but I believe with smarter data structs
	// should make this more efficient.

	Assignment assignment(A.getNumRows());
		
	Array2DMask M(A.getNumRows(), A.getNumCols());

	if(m_log != NULL) {
		m_log->input(A);
	}

	for(size_t i = 0; i < A.getNumRows(); ++i) {
		double min = numeric_limits<double>::infinity();
		size_t minRow = 0;
		size_t minCol = 0;

		for(Array2DMask::iterator row = M.begin(0); row != M.end(0); ++row) {
			for(Array2DMask::iterator col = M.begin(1); col != M.end(1); ++col) {
				const double& value = A.getEntry(*row, *col);
				if(min > value) {
					min = value;
					minRow = *row;
					minCol = *col;
				}
			}
		}

		if(m_log != NULL) {
			m_log->afterAssignment(A, assignment, minRow, minCol);
		}

		assignment[ minRow ] = minCol;
		M.erase(0, minRow);
		M.erase(1, minCol);
	}

	if(m_log != NULL) {
		m_log->output(A, assignment);
	}

	return assignment;
}

