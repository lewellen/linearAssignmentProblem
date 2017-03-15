#include <cstdlib>
#include <iostream>
#include <string>

#include "Array2D.h"
#include "Assignment.h"
#include "ISolver.h"
#include "ISolverFactory.h"
#include "ParallelDataGatherer.h"
#include "Stopwatch.h"

using std::cout;
using std::endl;
using std::ostream;
using std::string;

class RuntimeParallelDataGatherer : public ParallelDataGatherer {
public:

protected:
	bool excludeSolver(const string& name) {
		return 
			(name == ISolverFactory::SOLVER_BRUTE) ||
			(name == ISolverFactory::SOLVER_ATRANDOM); 
	}

	void onHeaderStart(ostream& ss) {
		ss << "size ";
	}

	void onHeaderSolver(ostream& ss, const string& name) {
		ss << name << " ";
	}

	void onHeaderEnd(ostream& ss) {
		ss << endl;
	}

	void onSampleStart(ostream& ss, const Array2D<double>& M) {
		ss << M.getNumRows() << " ";
	}

	void onSolverStart(ostream& ss, const Array2D<double>& M, ISolver& solver) {
		Stopwatch S;
		S.start();
		Assignment solverA = solver(M);
		S.stop();
		ss << S.elapsedSec() << " ";
	}

	void onSampleEnd(ostream& ss) {
		ss << endl;
	}
};

int main(int argc, char** argv) {
	RuntimeParallelDataGatherer g;

	SharedData shared;
	shared.solverNames = ISolverFactory::getValidNames(shared.numSolvers);
	shared.sizeMin = 1;
	shared.sizeMax = 1000;
	shared.coutLock = 0;

	const size_t numTasks = g.getNumLogicalProcessors();
	const size_t samplesPerTask = 15;

	Task tasks[numTasks];
	for(size_t i = 0; i < numTasks; ++i) {
		tasks[i].numSamples = samplesPerTask;
		tasks[i].shared = &shared;
	}

	g.run(tasks, numTasks);	

	return EXIT_SUCCESS;
}
