#include <cstdlib>
#include <iostream>

#include "Array2D.h"
#include "Assignment.h"
#include "ISolver.h"
#include "ISolverFactory.h"

using std::cout;
using std::endl;

typedef Array2D<double> CostMatrix;

CostMatrix randomMatrix(size_t size) {
	CostMatrix M(size);

	// Initialize random cost matrix
	for(size_t row = 0; row < M.getNumRows(); ++row) {
		for(size_t col = 0; col < M.getNumCols(); ++col) {
			M.getEntry(row, col) = (rand() % 100) + 5;
		}
	}

	return M;
}

int main(int argc, char** argv) {
	CostMatrix M = randomMatrix(12);

	ISolver* solver = ISolverFactory::make(ISolverFactory::SOLVER_HUNGARIAN);
	assert(solver != NULL);

	Assignment jobsByWorker = (*solver)(M);

	cout << "Assignment: " << endl;
	jobsByWorker.display(cout, M);

	cout << "Cost:\t" << jobsByWorker.cost(M) << endl;

	delete solver;

	return EXIT_SUCCESS;
}

