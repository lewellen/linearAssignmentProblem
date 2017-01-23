#include <list>
#include <iostream>
#include <utility>

#include "Array2DMask.h"
#include "ISolver.h"
#include "HungarianMethodSolver.h"

using std::cout;
using std::endl;
using std::list;
using std::pair;

HungarianMethodSolver::HungarianMethodSolver() {

}

HungarianMethodSolver::~HungarianMethodSolver() {

}

list<size_t> HungarianMethodSolver::operator() (Array2DMask& M) {
	list<size_t> assignments;

	cout << M << endl;

	// Deduct row min from each row
	for(Array2DMask::iterator row = M.rowBegin(); row != M.rowEnd(); ++row) {
		pair<double, size_t> rowMin = M.getRowMin(*row);
		for(Array2DMask::iterator col = M.colBegin(); col != M.colEnd(); ++col) {
			M.getEntry(*row, *col) -= rowMin.first;
		}
	}

	cout << M << endl;

	// Deduct col min from each column
	for(Array2DMask::iterator col = M.colBegin(); col != M.colEnd(); ++col) {
		pair<double, size_t> colMin = M.getColMin(*col);
		for(Array2DMask::iterator row = M.rowBegin(); row != M.rowEnd(); ++row) {
			M.getEntry(*row, *col) -= colMin.first;
		}
	}

	cout << M << endl;

	// Draw minimum number of lines through all zeros

	// If there are N lines; done.

	// Find the smallest entry not covered by any line. Subtract value from each row 
	// that is not crossed out; then add it to each column that *IS* crossed out.
	// go back to (draw min num lines through all zeros step.)

	return assignments;
}
