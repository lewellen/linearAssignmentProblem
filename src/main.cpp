#include <cstdlib>
#include <iostream>
#include <list>
#include <utility>

#include "Array2D.h"
#include "ISolver.h"
#include "ISolverFactory.h"

using std::cout;
using std::endl;
using std::list;
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
	vector<size_t> jobsByWorker = (*solver)(M);
	delete solver;	

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

	for(size_t worker = 0; worker < jobsByWorker.size(); ++worker) {
		cost += M.getEntry( worker, jobsByWorker[worker] );
	}

	cout << endl << "Cost: " << cost << endl;

	return EXIT_SUCCESS;
}
