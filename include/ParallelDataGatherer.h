#ifndef PARALLELDATAGATHERER_H
#define PARALLELDATAGATHERER_H

#include <atomic>
#include <cstdlib>
#include <iostream>
#include <string>

#include "Array2D.h"
#include "ISolver.h"

using std::atomic;
using std::string;
using std::ostream;

struct SharedData {
	size_t numSolvers;
	const string* solverNames;
	size_t sizeMin;
	size_t sizeMax;
	atomic<size_t> coutLock;
};

struct Task {
	SharedData* shared;
	size_t numSamples;
};

class ParallelDataGatherer;

struct ThreadStartArg {
	ParallelDataGatherer* gatherer;
	Task* task;

	ThreadStartArg() {
		gatherer = NULL;
		task = NULL;
	}

	ThreadStartArg(ParallelDataGatherer* gatherer, Task* task) {
		this->gatherer = gatherer;
		this->task = task;
	}
};

class ParallelDataGatherer {
public:
	void run(Task* tasks, size_t numTasks);
	size_t getNumLogicalProcessors() const;

protected:
	virtual bool excludeSolver(const string& name) = 0;

	virtual void onHeaderStart(ostream& safeOutput) = 0;
	virtual void onHeaderSolver(ostream& safeOutput, const string& name) = 0;
	virtual void onHeaderEnd(ostream& safeOutput) = 0;

	virtual void onSampleStart(ostream& safeOutput, const Array2D<double>& M) = 0;
	virtual void onSolverStart(ostream& safeOutput, const Array2D<double>& M, ISolver& solver) = 0;
	virtual void onSampleEnd(ostream& safeOutput) = 0;

private:
	static void staticThreadStart(ThreadStartArg& arg);

	void threadStart(Task& arg); 
};

#endif

