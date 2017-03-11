#include <cassert>
#include <iostream>
#include <limits>
#include <list>

#include "Array2D.h"
#include "Array2DMask.h"
#include "Assignment.h"
#include "ISolver.h"
#include "HungarianMethodSolver.h"

using std::cout;
using std::endl;
using std::list;
using std::numeric_limits;

HungarianMethodSolver::HungarianMethodSolver() {

}

HungarianMethodSolver::~HungarianMethodSolver() {

}

Assignment HungarianMethodSolver::operator() (const Array2D<double>& A) const {
	// Munkres, J. Algorithms for the Assignment and Transportation Problems.
	// Journal of the Society for Industrial and Applied Mathematics, Vol. 5,
	// No. 1 (Mar., 1957), 32-38.

	assert(A.getNumRows() == A.getNumCols());

	Array2D<double> B = A;

	// A_{i, j} = A_{i, j} - min_k A_{i, k} for all (i, j)
	for(size_t row = 0; row < B.getNumRows(); ++row) {
		double minValue = numeric_limits<double>::infinity();
		for(size_t col = 0; col < B.getNumCols(); ++col) {
			const double& value = B.getEntry(row, col);
			if(minValue > value) {
				minValue = value;
			}
		}

		for(size_t col = 0; col < B.getNumCols(); ++col) {
			double& value = B.getEntry(row, col);
			value -= minValue;
		}
	}

	// A_{i, j} = A_{i, j} - min_k A_{k, j} for all (i, j)
	for(size_t col = 0; col < B.getNumCols(); ++col) {
		double minValue = numeric_limits<double>::infinity();
		for(size_t row = 0; row < B.getNumRows(); ++row) {
			const double& value = B.getEntry(row, col);
			if(minValue > value) {
				minValue = value;
			}
		}

		for(size_t row = 0; row < B.getNumRows(); ++row) {
			double& value = B.getEntry(row, col);
			value -= minValue;
		}
	}

	// Keep tabs on which rows and columns are covered
	bool rowCovered[B.getNumRows()];
	bool colCovered[B.getNumCols()];

	memset(rowCovered, false, sizeof(bool) * B.getNumRows());
	memset(colCovered, false, sizeof(bool) * B.getNumCols());

	// Keep tabs on zeros that have been starred (ie assigned worker-job pairs)
	bool rowHasStar[B.getNumRows()];
	bool colHasStar[B.getNumCols()];

	memset(rowHasStar, false, sizeof(bool) * B.getNumRows());
	memset(colHasStar, false, sizeof(bool) * B.getNumCols());

	size_t rowsStarredCol[B.getNumRows()];
	size_t colsStarredRow[B.getNumCols()];

	for(size_t row = 0; row < B.getNumRows(); ++row) {
		rowsStarredCol[row] = B.getNumCols();
	}

	for(size_t col = 0; col < B.getNumCols(); ++col) {
		colsStarredRow[col] = B.getNumRows();
	}

	size_t numStarredZeros = 0;

	// Keep tabs on zeros that have been primed (ie candidate worker-job pairs)
	size_t rowsPrimedCol[B.getNumRows()];

	for(size_t row = 0; row < B.getNumRows(); ++row) {
		rowsPrimedCol[row] = B.getNumCols();
	}

	// Anticipate number of zeros << total number of entries
	typedef pair<size_t, size_t> Entry;
	list<Entry> zeros;

	for(size_t row = 0; row < B.getNumRows(); ++row) {
		for(size_t col = 0; col < B.getNumCols(); ++col) {
			const double& value = B.getEntry(row, col);
			if(value == 0) {
				zeros.push_back(Entry(row, col));
			}
		}
	}

	// Find a tenative assignment by going row-by-row and assigning wherever 
	// there's a zero in a column that doesn't already have an assigned zero.
	for(list<Entry>::iterator i = zeros.begin(); i != zeros.end(); ++i) {
		const Entry& entry = *i;
		const size_t& row = entry.first;
		const size_t& col = entry.second;

		if(!rowHasStar[row] && !colHasStar[col]) {
			rowHasStar[row] = true;
			colHasStar[col] = true;
			rowsStarredCol[row] = col;
			colsStarredRow[col] = row;

			colCovered[col] = true;
			++numStarredZeros;
		}
	}


	size_t iterations = B.getNumRows();
	while( (iterations-- > 0) && (numStarredZeros < B.getNumRows()) ) {
		bool didStep2 = false;
		for(list<Entry>::iterator i = zeros.begin(); i != zeros.end(); ++i) {
			const Entry& entry = *i;
			if(rowCovered[entry.first] || colCovered[entry.second]) {
				continue;
			}

			rowsPrimedCol[entry.first] = entry.second;

			if(! rowHasStar[entry.first] ) {
				// Step 2
				didStep2 = true;

				list<Entry> starred, primed;
				size_t row = entry.first;
				size_t col = entry.second;
				bool isPrime = true;

				size_t maxAttempts = B.getNumRows() * B.getNumCols();
				do {
					if(isPrime) {
						size_t nextRow = colsStarredRow[col];
						primed.push_back(Entry(row,col));
						if(nextRow < B.getNumRows()) {
							row = nextRow;
						} else {
							break;
						}
					} else {
						size_t nextCol = rowsPrimedCol[row];
						starred.push_back(Entry(row, col));
						if(nextCol < B.getNumCols()) {
							col = nextCol;
						} else {
							break;
						}
					}
				} while(--maxAttempts > 0);

				// All starred zeros in the sequence become unstarred.
				for(list<Entry>::iterator i = starred.begin(); i != starred.end(); ++i) {
					rowHasStar[(*i).first] = false ;
					colHasStar[(*i).second] = false ;
					rowsStarredCol[(*i).first] = B.getNumCols();
					colsStarredRow[(*i).second] = B.getNumRows();
					--numStarredZeros;
				}

				// All primed zeros in the sequence become starred
				for(list<Entry>::iterator i = primed.begin(); i != primed.end(); ++i) {
					rowHasStar[(*i).first] = true;
					colHasStar[(*i).second] = true;
					rowsStarredCol[(*i).first] = (*i).second;
					colsStarredRow[(*i).second] = (*i).first;
					++numStarredZeros;
				}

				// Erase all primes
				for(size_t r = 0; r < B.getNumRows(); ++r) {
					rowsPrimedCol[r] = B.getNumCols();
				}

				// Uncover all rows
				memset(rowCovered, false, sizeof(bool) * B.getNumRows());

				// Cover all cols containing a starred zero
				for(size_t c = 0; c < B.getNumCols(); ++c) {
					colCovered[c] = colsStarredRow[c] < B.getNumRows();
				}

				break;
			} else {
				rowCovered[entry.first] = true;
				colCovered[ rowsStarredCol[entry.first] ] = false;
			}
		} // Repeat until all zeros covered

		if(didStep2) {
			continue;
		}

		// Find the minimum uncovered value
		double minValue = numeric_limits<double>::infinity();
		for(size_t row = 0; row < B.getNumRows(); ++row) {
			if(!rowCovered[row]) {
				for(size_t col = 0; col < B.getNumCols(); ++col) {
					if(!colCovered[col]) {
						const double& value = B.getEntry(row, col);
						if(minValue > value) {
							minValue = value;
						}
					}
				}
			}
		}

		// Add min to each covered row
		for(size_t row = 0; row < B.getNumRows(); ++row) {
			if(rowCovered[row]) {
				for(size_t col = 0; col < B.getNumCols(); ++col) {
					double& value = B.getEntry(row, col);
					value += minValue;
				}
			}
		}

		// Subtract min from each uncovered col
		for(size_t col = 0; col < B.getNumCols(); ++col) {
			if(!colCovered[col]) {
				for(size_t row = 0; row < B.getNumRows(); ++row) {
					double& value = B.getEntry(row, col);
					value -= minValue;
				}
			}
		}

		// Refresh the list of zeros.
		zeros.clear();
		for(size_t row = 0; row < B.getNumRows(); ++row) {
			for(size_t col = 0; col < B.getNumCols(); ++col) {
				const double& value = B.getEntry(row, col);
				if(value == 0) {
					zeros.push_back(Entry(row, col));
				}
			}
		}
	}

	Assignment assignment(A.getNumRows());
	for(size_t row = 0; row < A.getNumRows(); ++row) {
		assignment[row] = rowsStarredCol[row];
	}
	return assignment;
}

