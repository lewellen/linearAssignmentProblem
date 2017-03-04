#include <cmath>
#include <cassert>
#include <limits>
#include <list>
#include <utility>

#include "Array2D.h"
#include "Array2DMask.h"
#include "Assignment.h"
#include "ISolver.h"
#include "GreedySolver.h"

#include <iostream>
using std::cout;
using std::endl;

using std::list;
using std::numeric_limits;
using std::pair;

GreedySolver::GreedySolver() {

}

GreedySolver::~GreedySolver() {

}

Assignment GreedySolver::operator() (const Array2D<double>& A) const {
	assert(A.getNumRows() == A.getNumCols());

	// As written this is O(n^3), but I believe with smarter data structs
	// should make this more efficient.

	Assignment assignment(A.getNumRows());
		
	Array2DMask M(A.getNumRows(), A.getNumCols());

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

		assignment[ minRow ] = minCol;
		M.erase(0, minRow);
		M.erase(1, minCol);
	}

	return assignment;
}

