#include <cstdlib>
#include <iostream>
#include <list>
#include <utility>

#include "CostMatrix.h"
#include "ISolver.h"
#include "ISolverFactory.h"

using std::cout;
using std::endl;
using std::list;
using std::pair;

int main(int argc, char** argv) {
	CostMatrix M(5);

	// Initialize random cost matrix
	for(CostMatrix::iterator row = M.rowBegin(); row != M.rowEnd(); ++row) {
		for(CostMatrix::iterator col = M.colBegin(); col != M.colEnd(); ++col) {
			M.getEntry(*row, *col) = (rand() % 100) + 5;
		}
	}

	ISolver* solver = ISolverFactory::make(ISolverFactory::SOLVER_ALTERNATIVE);
	assert(solver != NULL);

	list< pair<size_t, size_t> > assignments = (*solver)(M);

	delete solver;

	double cost = 0.0;
	for(list< pair<size_t, size_t> >::const_iterator i = assignments.begin(); i != assignments.end(); ++i) {
		const pair<size_t, size_t>& assignment = *i;
		cost += M.getEntry(assignment.first, assignment.second);
	}

	cout << "Cost: " << cost << endl;

	return EXIT_SUCCESS;
}
