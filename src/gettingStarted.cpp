#include <cstdlib>
#include <iostream>

#include "Array2D.h"
#include "Assignment.h"
#include "ISolver.h"
#include "ISolverFactory.h"
#include "RandomMatrix.h"

using std::cout;
using std::endl;

int main(int argc, char** argv) {
	RandomMatrix M = RandomMatrix(12, 12);

	ISolver* solver = ISolverFactory::make(ISolverFactory::SOLVER_HUNGARIAN);
	assert(solver != NULL);

	Assignment jobsByWorker = (*solver)(M);

	cout << "Assignment: " << endl;
	jobsByWorker.display(cout, M);

	cout << "Cost:\t" << jobsByWorker.cost(M) << endl;

	delete solver;

	return EXIT_SUCCESS;
}

