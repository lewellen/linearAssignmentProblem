#include <cmath>
#include <cstdlib>
#include <iostream>
#include <list>
#include <map>
#include <utility>

#include "Array2D.h"
#include "Assignment.h"
#include "IObjective.h"
#include "IObjectiveFactory.h"
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
	map<size_t, map<string, SampledValue> > profile;
	map<size_t, map<string, Stopwatch> > timers;

	size_t numSolvers;
	const string* solverNames = ISolverFactory::getValidNames(numSolvers);

	ISolver* brute = ISolverFactory::make(ISolverFactory::SOLVER_BRUTE);

	size_t sizeMin = 2;
	size_t sizeMax = 10;

	for(size_t size = sizeMin; size <= sizeMax; ++size) {
		bool repeat = true;
		while(repeat) {
			CostMatrix M = randomMatrix(size);
			Assignment bruteMinA = (*brute)(M);
			double bruteMinACost = bruteMinA.cost(M);

			IObjective* maxObj = IObjectiveFactory::make(IObjectiveFactory::OBJECTIVE_MAXIMIZE);
			CostMatrix N = M;
			(*maxObj)(N);
			delete maxObj;

			Assignment bruteMaxA = (*brute)(N);
			double bruteMaxACost = bruteMaxA.cost(M);

			if(bruteMinACost == bruteMaxACost) {
				continue;
			}

			assert(bruteMaxACost > bruteMinACost);

			repeat = false;
			for(size_t solverIndex = 0; solverIndex < numSolvers; ++solverIndex) {
				const string& solverName = solverNames[solverIndex];
				if(solverName == ISolverFactory::SOLVER_BRUTE) {
					continue;
				}

				SampledValue& samples = profile[size][solverName];
				if(samples.numSamples() >= 60) {
					continue;
				}

				Stopwatch& R = timers[size][solverName];
				if(samples.numSamples() == 0) {
					R.start();
				} else {
					R.stop();
				}

				if(R.elapsedMs() >= 0.5 * 60 * 1000) {
					continue;
				}
		
				ISolver* solver = ISolverFactory::make(solverName);
				assert(solver != NULL);

				Assignment solverA = (*solver)(M);
				double solverACost = solverA.cost(M);

				samples.add( (solverACost - bruteMinACost) / (bruteMaxACost - bruteMinACost) );	
				delete solver;
				repeat = true;
			}
		} 
	}

	delete brute;

	cout << "N\t";
	for(size_t solverIndex = 0; solverIndex < numSolvers; ++solverIndex) {
		const string& solverName = solverNames[solverIndex];
		if(solverName == ISolverFactory::SOLVER_BRUTE) {
			continue;
		}

		cout << solverName << "\tstdDev";
		if(solverIndex + 1 != numSolvers) {
			cout << "\t";
		}
	}
	cout << endl;

	for(size_t size = sizeMin; size <= sizeMax; ++size) {
		cout << size << "\t";
		for(size_t solverIndex = 0; solverIndex < numSolvers; ++solverIndex) {
			const string& solverName = solverNames[solverIndex];
			if(solverName == ISolverFactory::SOLVER_BRUTE) {
				continue;
			}

			double average = 0;
			double stdev = 0;

			const SampledValue& samples = profile[size][solverName];
			//assert(!samples.empty());
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
