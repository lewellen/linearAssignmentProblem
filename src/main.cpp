#include <cstdlib>
#include <iostream>
#include <list>
#include <map>
#include <utility>

#include "Array2D.h"
#include "ISolver.h"
#include "ISolverFactory.h"

using std::cout;
using std::endl;
using std::list;
using std::map;
using std::pair;

int main(int argc, char** argv) {
	typedef Array2D<double> CostMatrix;

	CostMatrix M(10);

	// Initialize random cost matrix
	for(size_t row = 0; row < M.getNumRows(); ++row) {
		for(size_t col = 0; col < M.getNumCols(); ++col) {
			M.getEntry(row, col) = (rand() % 100) + 5;
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

	for(size_t row = 0; row < M.getNumRows(); ++row) {
		size_t assignedCol = jobsByWorker[row];

		for(size_t col = 0; col < M.getNumCols(); ++col) {
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
