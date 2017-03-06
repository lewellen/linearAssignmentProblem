#include <cmath>
#include <cstdlib>
#include <iostream>
#include <list>
#include <map>
#include <utility>

#include "Array2D.h"
#include "Assignment.h"
#include "ISolver.h"
#include "ISolverFactory.h"
#include "SampledValue.h"
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

	map<size_t, map<string, SampledValue > > profile;

	size_t numSolvers;
	const string* solverNames = ISolverFactory::getValidNames(numSolvers);
	for(size_t solverIndex = 0; solverIndex < numSolvers; ++solverIndex) {
		const string& solverName = solverNames[solverIndex];
		if(solverName == ISolverFactory::SOLVER_ATRANDOM) {
			continue;
		}

		ISolver* solver = ISolverFactory::make(solverName);
		assert(solver != NULL);

		for(size_t size = 2; size <= 12; ++size) {
			SampledValue& samples = profile[size][solverName];

			Stopwatch R;
			R.start();
			do {
				CostMatrix M = randomMatrix(size);
				S.start();
				Assignment jobsByWorker = (*solver)(M);
				S.stop();
			
				samples.add( S.elapsedMs() );

				R.stop();
			} while(R.elapsedMs() < 1 * 60 * 1000 && samples.numSamples() < 30 ); 
		}

		delete solver;	
	}

	cout << "N\t";
	for(size_t solverIndex = 0; solverIndex < numSolvers; ++solverIndex) {
		const string& solverName = solverNames[solverIndex];
		if(solverName == ISolverFactory::SOLVER_ATRANDOM) {
			continue;
		}

		cout << solverName << "\tstdDev";
		if(solverIndex + 1 != numSolvers) {
			cout << "\t";
		}
	}
	cout << endl;

	for(size_t size = 2; size <= 12; ++size) {
		cout << size << "\t";
		for(size_t solverIndex = 0; solverIndex < numSolvers; ++solverIndex) {
			const string& solverName = solverNames[solverIndex];
			if(solverName == ISolverFactory::SOLVER_ATRANDOM) {
				continue;
			}

			double average = 0;
			double stdev = 0;

			const SampledValue& samples = profile[size][solverName];
			if(!samples.empty()) {
				average = samples.sampleMean();
				stdev = samples.sampleStandardDev();
			}

			cout << average << "\t" << stdev;
			if(solverIndex + 1 != numSolvers) {
				cout << "\t";
			}
		}
		cout << endl;
	}

	return EXIT_SUCCESS;
}
