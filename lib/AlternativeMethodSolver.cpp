#include <cmath>
#include <cassert>
#include <limits>
#include <list>
#include <utility>

#include "Array2D.h"
#include "Array2DMask.h"
#include "Assignment.h"
#include "ISolver.h"
#include "AlternativeMethodSolver.h"

#include <iostream>
using std::cout;
using std::endl;

using std::list;
using std::numeric_limits;
using std::pair;

AlternativeMethodSolver::AlternativeMethodSolver() {

}

AlternativeMethodSolver::~AlternativeMethodSolver() {

}

Assignment AlternativeMethodSolver::operator() (const Array2D<double>& A) const {
	assert(A.getNumRows() == A.getNumCols());

	Assignment assignment(A.getNumRows());

	Array2D<double> B = A;
		
	Array2DMask M(B.getNumRows(), B.getNumCols());

	size_t count = 0;
	while( M.begin(0) != M.end(0)  && count++ < B.getNumRows() ) {
		for(Array2DMask::iterator row = M.begin(0); row != M.end(0); ++row) {
			double min = numeric_limits<double>::infinity();
			for(Array2DMask::iterator col = M.begin(1); col != M.end(1); ++col) {
				const double& value = B.getEntry(*row, *col);
				if(min > value) {
					min = value;
				}
			}

			if(min > 0) {
				for(Array2DMask::iterator col = M.begin(1); col != M.end(1); ++col) {
					double& value = B.getEntry(*row, *col);
					value -= min;
				}
			}
		}

/*		cout << "1:" << endl;
		for(Array2DMask::iterator row = M.begin(0); row != M.end(0); ++row) {
			for(Array2DMask::iterator col = M.begin(1); col != M.end(1); ++col) {
				const double& value = B.getEntry(*row, *col);
				cout << value << " ";
			}
			cout << endl;
		}
*/
		for(Array2DMask::iterator col = M.begin(1); col != M.end(1); ++col) {
			double min = numeric_limits<double>::infinity();
			for(Array2DMask::iterator row = M.begin(0); row != M.end(0); ++row) {
				const double& value = B.getEntry(*row, *col);
				if(min > value) {
					min = value;
				}
			}

			if(min > 0) {
				for(Array2DMask::iterator row = M.begin(0); row != M.end(0); ++row) {
					double& value = B.getEntry(*row, *col);
					value -= min;
				}
			}
		}
/*
		cout << "2:" << endl;
		for(Array2DMask::iterator row = M.begin(0); row != M.end(0); ++row) {
			for(Array2DMask::iterator col = M.begin(1); col != M.end(1); ++col) {
				const double& value = B.getEntry(*row, *col);
				cout << value << " ";
			}
			cout << endl;
		}*/


		for(Array2DMask::iterator row = M.begin(0); row != M.end(0); ++row) {
			size_t colWithZero = B.getNumCols();
			for(Array2DMask::iterator col = M.begin(1); col != M.end(1); ++col) {
				const double& value = B.getEntry(*row, *col);
				if(fabs(value) < 1e-9) {
					if(colWithZero == B.getNumCols()) {
						colWithZero = *col;
					} else {
						colWithZero = B.getNumCols();
						break;
					}
				}
			}
			if(colWithZero != B.getNumCols()) {
			//	cout << *row << "-" << colWithZero << endl;
				assignment[*row] = colWithZero;
				M.erase(0, *row);
				M.erase(1, colWithZero);
			}
		}


		list< pair<size_t, size_t> > colsWithSingleZero;
		for(Array2DMask::iterator col = M.begin(1); col != M.end(1); ++col) {
			size_t rowWithZero = B.getNumRows();
			for(Array2DMask::iterator row = M.begin(0); row != M.end(0); ++row) {
				const double& value = B.getEntry(*row, *col);
				if(fabs(value) < 1e-9) {
					if(rowWithZero == B.getNumRows()) {
						rowWithZero = *row;
					} else {
						rowWithZero = B.getNumRows();
						break;
					}
				}
			}
			if(rowWithZero != B.getNumRows()) {
			//	cout << rowWithZero << "-" << *col << endl;
				assignment[rowWithZero] = *col;
				M.erase(0, rowWithZero);
				M.erase(1, *col);
			}
		}
	}	


	return assignment;
}

