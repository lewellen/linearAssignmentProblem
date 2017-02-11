#include <cstdlib>
#include <iostream>

#include "Array2D.h"
#include "ISolver.h"
#include "ISolverFactory.h"

#define cout cout << __FILE__ << ":" << __LINE__ << "\t"

#define ASSERT_EQUALS(x, y) if(x != y) { std::cout << #x << " != " << #y << "\t(" << x << " != " << y << ")" << std::endl; return; }

typedef Array2D<double> CostMatrix;

void testSolve(const CostMatrix& M, const vector<size_t>& expected, const string& solverName) {
	ISolver* solver = ISolverFactory::make(solverName);
	vector<size_t> actual = (*solver)(M);
	delete solver;

	ASSERT_EQUALS(expected.size(), actual.size());
	for(size_t i = 0; i < expected.size(); ++i) {
		ASSERT_EQUALS(expected[i], actual[i]);
	}
}

void testSolve(const CostMatrix& M, const vector<size_t>& expected) {
	size_t numNames;
	const string* validNames = ISolverFactory::getValidNames(numNames);

	for(size_t i = 0; i < numNames; ++i) {
		testSolve(M, expected, validNames[i]);
	}
}

void testEasy() {
	// http://www.hungarianalgorithm.com/examplehungarianalgorithm.php
	CostMatrix M(4, 4);

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
	
	vector<size_t> expected(4);
	expected[0] = 2;
	expected[1] = 1;
	expected[2] = 0;
	expected[3] = 3;

	testSolve(M, expected, ISolverFactory::SOLVER_BRUTE);
}

int main(int argc, char** argv) {
	testEasy();

	return EXIT_SUCCESS;
}
