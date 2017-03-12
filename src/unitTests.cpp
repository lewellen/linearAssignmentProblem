#include <cstdlib>
#include <iostream>

#include "Array.h"
#include "Array2D.h"
#include "Assignment.h"
#include "ISolver.h"
#include "ISolverFactory.h"
#include "IInputFormat.h"
#include "IInputFormatFactory.h"
#include "IOutputFormat.h"
#include "IOutputFormatFactory.h"

using std::cout;
using std::endl;

#define cout cout << __FILE__ << ":" << __LINE__ << "\t"

#define ASSERT_EQUALS(x, y) if(x != y) { cout << #x << " != " << #y << "\t(" << x << " != " << y << ")" << endl; return false; }

#define FAIL cout << "FAIL\t" << __FUNCTION__ << endl;
#define PASS cout << "PASS\t" << __FUNCTION__ << endl;

#define RUN(x) if(x) { PASS; } else { FAIL; }

bool testArray() {
	Array<double> A(4);
	for(size_t i = 0; i < A.getSize(); ++i) {
		A[i] = i;
	}

	for(size_t i = 0; i < A.getSize(); ++i) {
		ASSERT_EQUALS(A[i], i);
	}

	return true;
}

bool testArray2DCopyConstructor() {
	const size_t N = 4;
	Array2D<double> A(N, N);

	for(size_t row = 0; row < A.getNumRows(); ++row) {
		for(size_t col = 0; col < A.getNumCols(); ++col) {
			A.getEntry(row, col) = row * A.getNumRows() + col;
		}
	}

	Array2D<double> B = A;

	ASSERT_EQUALS(A.getNumRows(), B.getNumRows());
	ASSERT_EQUALS(A.getNumCols(), B.getNumCols());

	for(size_t row = 0; row < B.getNumRows(); ++row) {
		for(size_t col = 0; col < B.getNumCols(); ++col) {
			ASSERT_EQUALS(A.getEntry(row, col), B.getEntry(row, col));
		}
	}

	return true;
}

bool testSolve(const Array2D<double>& M, const Assignment& expected, const string& solverName) {
	ISolver* solver = ISolverFactory::make(solverName);
	Assignment actual = (*solver)(M);
	delete solver;

	ASSERT_EQUALS(expected.size(), actual.size());
	for(size_t i = 0; i < expected.size(); ++i) {
		ASSERT_EQUALS(expected[i], actual[i]);
	}

	return true;
}

void testBruteMethodSolve() {
	// http://www.hungarianalgorithm.com/examplehungarianalgorithm.php
	Array2D<double> M(4, 4);

	M.getEntry(0, 0) = 82;
	M.getEntry(0, 1) = 83;
	M.getEntry(0, 2) = 69;
	M.getEntry(0, 3) = 92;

	M.getEntry(1, 0) = 77;
	M.getEntry(1, 1) = 37;
	M.getEntry(1, 2) = 49;
	M.getEntry(1, 3) = 92;

	M.getEntry(2, 0) = 11;
	M.getEntry(2, 1) = 69;
	M.getEntry(2, 2) = 5;
	M.getEntry(2, 3) = 86;

	M.getEntry(3, 0) = 8;
	M.getEntry(3, 1) = 9;
	M.getEntry(3, 2) = 98;
	M.getEntry(3, 3) = 23;
	
	Assignment expected(4);
	expected[0] = 2;
	expected[1] = 1;
	expected[2] = 0;
	expected[3] = 3;

	RUN( testSolve(M, expected, ISolverFactory::SOLVER_BRUTE) );
}

void testHungarianMethodSolveEasy() {
	// Combinatorial Optimization pg. 252
	Array2D<double> M(5, 5);

	M.getEntry(0, 0) = 7;
	M.getEntry(0, 1) = 2;
	M.getEntry(0, 2) = 1;
	M.getEntry(0, 3) = 9;
	M.getEntry(0, 4) = 4;

	M.getEntry(1, 0) = 9;
	M.getEntry(1, 1) = 6;
	M.getEntry(1, 2) = 9;
	M.getEntry(1, 3) = 5;
	M.getEntry(1, 4) = 5;

	M.getEntry(2, 0) = 3;
	M.getEntry(2, 1) = 8;
	M.getEntry(2, 2) = 3;
	M.getEntry(2, 3) = 1;
	M.getEntry(2, 4) = 8;

	M.getEntry(3, 0) = 7;
	M.getEntry(3, 1) = 9;
	M.getEntry(3, 2) = 4;
	M.getEntry(3, 3) = 2;
	M.getEntry(3, 4) = 2;

	M.getEntry(4, 0) = 8;
	M.getEntry(4, 1) = 4;
	M.getEntry(4, 2) = 7;
	M.getEntry(4, 3) = 4;
	M.getEntry(4, 4) = 8;

	Assignment expected(5);
	expected[0] = 2;
	expected[1] = 4;
	expected[2] = 0;
	expected[3] = 3;
	expected[4] = 1;

	RUN( testSolve(M, expected, ISolverFactory::SOLVER_HUNGARIAN) );
}

int main(int argc, char** argv) {
	RUN( testArray() );
	RUN( testArray2DCopyConstructor() );

//	testBruteMethodSolve();
//	testHungarianMethodSolveEasy();

	return EXIT_SUCCESS;
}
