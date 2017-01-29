#include <cassert>
#include <vector>
#include <iostream>
#include <utility>

#include "Array2D.h"
#include "ISolver.h"
#include "HungarianMethodSolver.h"

using std::cout;
using std::endl;
using std::vector;
using std::pair;

HungarianMethodSolver::HungarianMethodSolver() {

}

HungarianMethodSolver::~HungarianMethodSolver() {

}

vector<size_t> HungarianMethodSolver::operator() (const Array2D<double>& A) const {
	assert(A.getNumRows() == A.getNumCols());

	vector<size_t> assignments;

/*	Array2D M = A; // explicit copy

	cout << M << endl;

	// Deduct row min from each row
	for(Array2D::iterator row = M.rowBegin(); row != M.rowEnd(); ++row) {
		pair<double, size_t> rowMin = M.getRowMin(*row);
		for(Array2D::iterator col = M.colBegin(); col != M.colEnd(); ++col) {
			M.getEntry(*row, *col) -= rowMin.first;
		}
	}

	cout << M << endl;

	// Deduct col min from each column
	for(Array2D::iterator col = M.colBegin(); col != M.colEnd(); ++col) {
		pair<double, size_t> colMin = M.getColMin(*col);
		for(Array2D::iterator row = M.rowBegin(); row != M.rowEnd(); ++row) {
			M.getEntry(*row, *col) -= colMin.first;
		}
	}

	cout << M << endl;

	// Draw minimum number of lines through all zeros

	// If there are N lines; done.

	// Find the smallest entry not covered by any line. Subtract value from each row 
	// that is not crossed out; then add it to each column that *IS* crossed out.
	// go back to (draw min num lines through all zeros step.)
*/
	return assignments;
}

