#include <cstdlib>
#include <iostream>
#include <list>
#include <map>
#include <utility>

#include "CostMatrix.h"
#include "ISolver.h"
#include "ISolverFactory.h"

using std::cout;
using std::endl;
using std::list;
using std::map;
using std::pair;

int main(int argc, char** argv) {
	CostMatrix M(10);

	// Initialize random cost matrix
	srand(time(NULL));
	for(CostMatrix::iterator row = M.rowBegin(); row != M.rowEnd(); ++row) {
		for(CostMatrix::iterator col = M.colBegin(); col != M.colEnd(); ++col) {
			M.getEntry(*row, *col) = (rand() % 100) + 5;
		}
	}

	ISolver* solver = ISolverFactory::make(ISolverFactory::SOLVER_BRUTE);
	assert(solver != NULL);
	list<size_t> assignments = (*solver)(M);
	delete solver;

	map<size_t, size_t> jobsByWorker;
	size_t job = 0;
	for(list<size_t>::const_iterator i = assignments.begin(); i != assignments.end(); ++i) {
		jobsByWorker[*i] = job;
		++job;
	}

	for(CostMatrix::iterator i = M.rowBegin(); i != M.rowEnd(); ++i) {
		size_t row = *i;
		size_t assignedCol = jobsByWorker[row];

		for(CostMatrix::iterator j = M.colBegin(); j != M.colEnd(); ++j) {
			size_t col = *j;

			if(col == assignedCol) {
				cout << "[";
			} else {
				cout << " ";
			}

			cout << M.getEntry(row, col);

			if(col == assignedCol) {
				cout << "]";
			} else {
				cout << " ";
			}

			cout << " ";
		}

		cout << endl;
	}

	double cost = 0.0;

	for(map<size_t, size_t>::const_iterator i = jobsByWorker.begin(); i != jobsByWorker.end(); ++i) {
		cost += M.getEntry( (*i).first, (*i).second );
	}

	cout << endl << "Cost: " << cost << endl;

	return EXIT_SUCCESS;
}
