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
#include "RandomMatrix.h"
#include "Stopwatch.h"

using std::cout;
using std::endl;
using std::list;
using std::map;
using std::pair;

int main(int argc, char** argv) {
	map<size_t, map<string, Stopwatch> > timers;

	size_t numSolvers;
	const string* solverNames = ISolverFactory::getValidNames(numSolvers);

	const string& baselineName = ISolverFactory::SOLVER_HUNGARIAN;
	ISolver* baseline = ISolverFactory::make(baselineName);
	assert(baseline != NULL);

	const size_t sizeMin = 2;
	const size_t sizeMax = 512;
	const size_t numSamples = 60;

	cout << "size " << baselineName << "_MIN" << " " << baselineName << "_MAX" << " ";
	for(size_t solverIndex = 0; solverIndex < numSolvers; ++solverIndex) {
		const string& solverName = solverNames[solverIndex];
		if(
			(solverName == ISolverFactory::SOLVER_BRUTE) ||
			(solverName == baselineName) 
		) {
			continue;
		}
		cout << solverName << " ";
	}
	cout << endl;


	for(size_t size = sizeMin; size <= sizeMax; size += 10) {
		for(size_t sample = 0; sample < numSamples; ++sample) {
			RandomMatrix M = RandomMatrix(size, size);
			Assignment baselineMinA = (*baseline)(M);
			double baselineMinACost = baselineMinA.cost(M);

			IObjective* maxObj = IObjectiveFactory::make(IObjectiveFactory::OBJECTIVE_MAXIMIZE);
			Array2D<double> N = M;
			(*maxObj)(N);
			delete maxObj;

			Assignment baselineMaxA = (*baseline)(N);
			double baselineMaxACost = baselineMaxA.cost(M);

			if(baselineMinACost == baselineMaxACost) {
				continue;
			}

			cout << size << " " << baselineMinACost << " " << baselineMaxACost << " ";

			for(size_t solverIndex = 0; solverIndex < numSolvers; ++solverIndex) {
				const string& solverName = solverNames[solverIndex];
				if(
					(solverName == ISolverFactory::SOLVER_BRUTE) ||
					(solverName == baselineName) 
				) {
					continue;
				}
	
				ISolver* solver = ISolverFactory::make(solverName);
				assert(solver != NULL);

				Assignment solverA = (*solver)(M);
				double solverACost = solverA.cost(M);

				cout << solverACost << " ";

				delete solver;
			}

			cout << endl;
		} 
	}

	delete baseline;

	return EXIT_SUCCESS;
}
