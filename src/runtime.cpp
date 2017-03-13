#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "ISolver.h"
#include "ISolverFactory.h"
#include "RandomMatrix.h"
#include "Stopwatch.h"

using std::cout;
using std::endl;
using std::map;
using std::string;

bool excludeSolver(const string& solverName) {
	return 
		(solverName == ISolverFactory::SOLVER_BRUTE) ||
		(solverName == ISolverFactory::SOLVER_ATRANDOM);
}

int main(int argc, char** argv) {
	map<size_t, map<string, Stopwatch> > timers;

	size_t numSolvers;
	const string* solverNames = ISolverFactory::getValidNames(numSolvers);

	const size_t sizeMin = 2;
	const size_t sizeMax = 512;
	const size_t numSamples = 10;

	cout << "size ";
	for(size_t solverIndex = 0; solverIndex < numSolvers; ++solverIndex) {
		const string& solverName = solverNames[solverIndex];
		if(!excludeSolver(solverName)) {
			cout << solverName << " ";
		}
	}
	cout << endl;

	for(size_t size = sizeMin; size <= sizeMax; size *= 2) {
		for(size_t sample = 0; sample < numSamples; ++sample) {
			RandomMatrix M = RandomMatrix(size, size);

			cout << size << " ";

			for(size_t solverIndex = 0; solverIndex < numSolvers; ++solverIndex) {
				const string& solverName = solverNames[solverIndex];
				if(!excludeSolver(solverName)) {	
					ISolver* solver = ISolverFactory::make(solverName);
					assert(solver != NULL);

					Stopwatch S;
					S.start();
					Assignment solverA = (*solver)(M);
					S.stop();

					cout << S.elapsedSec() << " ";

					delete solver;
				}
			}

			cout << endl;
		} 
	}

	return EXIT_SUCCESS;
}
