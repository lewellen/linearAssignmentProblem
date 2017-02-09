#include <cassert>
#include <iostream>
#include <limits>
#include <list>
#include <utility>
#include <vector>

#include "Array2D.h"
#include "Array2DMask.h"
#include "ISolver.h"
#include "HungarianMethodSolver.h"

using std::cout;
using std::endl;
using std::list;
using std::numeric_limits;
using std::pair;
using std::vector;

HungarianMethodSolver::HungarianMethodSolver() {

}

HungarianMethodSolver::~HungarianMethodSolver() {

}

vector<size_t> HungarianMethodSolver::operator() (const Array2D<double>& A) const {
	assert(A.getNumRows() == A.getNumCols());

	vector<size_t> assignments(A.getNumRows());

	Array2D<double> B = A; // explicit copy

	while(true) {
		Array2DMask M(B.getNumRows(), B.getNumCols());

		// Deduct row min from each row
		for(Array2DMask::iterator row = M.begin(0); row != M.end(0); ++row) {
			double minValue = numeric_limits<double>::infinity();
			size_t minIndex = 0;
			for(Array2DMask::iterator col = M.begin(1); col != M.end(1); ++col) {
				double value = B.getEntry( *row, *col );
				if(minValue > value) {
					minValue = value;
					minIndex = *col;
				}
			}

			for(Array2DMask::iterator col = M.begin(1); col != M.end(1); ++col) {
				double value = B.getEntry( *row, *col );
				B.getEntry(*row, *col) = value - minValue;
			}
		}


		// Deduct col min from each column
		for(Array2DMask::iterator col = M.begin(1); col != M.end(1); ++col) {
			double minValue = numeric_limits<double>::infinity();
			size_t minIndex = 0;
			for(Array2DMask::iterator row = M.begin(0); row != M.end(0); ++row) { 
				double value = B.getEntry(*row, *col);
				if(minValue > value) {
					minValue = value;
					minIndex = *row;
				}
			}

			for(Array2DMask::iterator row = M.begin(0); row != M.end(0); ++row) {
				double value = B.getEntry(*row, *col);
				B.getEntry(*row, *col) = value - minValue;
			}
		}

		// Draw minimum number of lines through all zeros. (Munkres, Konig, Ford-Fulkerson)
		list<size_t> verticalLines, horizontalLines;
		size_t numLines = findZeroCovering(B, verticalLines, horizontalLines);

		// If there are N lines; done.
		if(numLines == B.getNumRows()) {
			return assignments;
		}

		// Find the smallest entry not covered by any line. 
		for(list<size_t>::const_iterator i = horizontalLines.begin(); i != horizontalLines.end(); ++i) {
			M.erase(0, *i);
		}

		for(list<size_t>::const_iterator i = verticalLines.begin(); i != verticalLines.end(); ++i) {
			M.erase(1, *i);
		}

		double minValue = numeric_limits<double>::infinity();
		for(Array2DMask::iterator row = M.begin(0); row != M.end(0); ++row) {
			for(Array2DMask::iterator col = M.begin(1); col != M.end(1); ++col) {
				double value = B.getEntry(*row, *col);
				if(minValue > value) {
					minValue = value;
				}
			}
		}

		// Deduct the minimum value from all uncovered entries, and then
		// increment each entry covered by two lines.
		for(Array2DMask::iterator row = M.begin(0); row != M.end(0); ++row) {
			for(Array2DMask::iterator col = M.begin(1); col != M.end(1); ++col) {
				double value = B.getEntry(*row, *col);
				B.getEntry(*row, *col) = value - minValue;
			}
		}

		for(list<size_t>::const_iterator row = horizontalLines.begin(); row != horizontalLines.end(); ++row) {
			for(list<size_t>::const_iterator col = verticalLines.begin(); col != verticalLines.end(); ++col) {
				double value = B.getEntry(*row, *col);
				B.getEntry(*row, *col) = value + minValue;
			}
		}
	}

	return assignments;
}

size_t HungarianMethodSolver::findZeroCovering(
	const Array2D<double>& B, 
	list<size_t>& verticalLines, list<size_t>& horizontalLines) const {

	return 0;
}
