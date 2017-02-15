#include <cstdlib>
#include <iostream>
#include <list>
#include <map>
#include <utility>

#include "Array2D.h"
#include "Assignment.h"
#include "ISolver.h"
#include "ISolverFactory.h"
#include "Stopwatch.h"

using std::cout;
using std::endl;
using std::list;
using std::map;
using std::pair;

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
	Stopwatch S;

	map<size_t, map<string, double> > profile;

	size_t numSolvers;
	const string* solverNames = ISolverFactory::getValidNames(numSolvers);
	for(size_t solverIndex = 0; solverIndex < numSolvers; ++solverIndex) {
		const string& solverName = solverNames[solverIndex];
		ISolver* solver = ISolverFactory::make(solverName);
		assert(solver != NULL);

		for(size_t size = 2; size <= 12; ++size) {
			CostMatrix M = randomMatrix(size);
			S.start();
			Assignment jobsByWorker = (*solver)(M);
			S.stop();

			profile[size][solverName] = S.elapsedMs();
		}

		delete solver;	
	}

	cout << "N\t";
	for(size_t solverIndex = 0; solverIndex < numSolvers; ++solverIndex) {
		cout << solverNames[solverIndex];
		if(solverIndex + 1 != numSolvers) {
			cout << "\t";
		}
	}
	cout << endl;

	for(size_t size = 2; size <= 12; ++size) {
		cout << size << "\t";
		for(size_t solverIndex = 0; solverIndex < numSolvers; ++solverIndex) {
			cout << profile[size][ solverNames[solverIndex] ];
			if(solverIndex + 1 != numSolvers) {
				cout << "\t";
			}
		}
		cout << endl;
	}

	return EXIT_SUCCESS;
}
