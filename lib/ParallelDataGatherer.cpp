#include <atomic>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <sstream>
#include <string>
#include <thread>

#include "ISolver.h"
#include "ISolverFactory.h"
#include "ParallelDataGatherer.h"
#include "RandomMatrix.h"

using std::atomic;
using std::atomic_compare_exchange_weak;
using std::cout;
using std::endl;
using std::string;
using std::thread;
using std::ostringstream;

void ParallelDataGatherer::run(Task* tasks, size_t numTasks) {
	assert(tasks != NULL);
	assert(numTasks != 0);

	ThreadStartArg stasks[numTasks];
	for(size_t i = 0; i < numTasks; ++i) {
		stasks[i] = ThreadStartArg(this, &tasks[i]);
	}

	onHeaderStart(cout);
	for(size_t solverIndex = 0; solverIndex < tasks[0].shared->numSolvers; ++solverIndex) {
		const string& solverName = tasks[0].shared->solverNames[solverIndex];
		if(!excludeSolver(solverName)) {
			onHeaderSolver(cout, solverName);
		}
	}
	onHeaderEnd(cout);

	size_t numThreads = numTasks - 1;
	thread threads[numThreads];
	for(size_t i = 0; i < numThreads; ++i) {
		threads[i] = thread(staticThreadStart, std::ref(stasks[i])); 
	}

	threadStart(tasks[numThreads]);

	for(size_t i = 0; i < numThreads; ++i) {
		threads[i].join();
	}
}

size_t ParallelDataGatherer::getNumLogicalProcessors() const {
	size_t n = thread::hardware_concurrency();
	if(n == 0) {
		n = 1;
	}

	return n;
}

void ParallelDataGatherer::staticThreadStart(ThreadStartArg& arg) {
	assert(arg.gatherer != NULL);
	assert(arg.task != NULL);

	arg.gatherer->threadStart(*arg.task);
}

void ParallelDataGatherer::threadStart(Task& task) {
	assert(task.shared != NULL);

	size_t inc = 1;
	for(size_t size = task.shared->sizeMin; size <= task.shared->sizeMax; size += inc) {
		for(size_t sample = 0; sample < task.numSamples; ++sample) {
			RandomMatrix M = RandomMatrix(size, size);

			ostringstream ss;
			onSampleStart(ss, M);

			for(size_t solverIndex = 0; solverIndex < task.shared->numSolvers; ++solverIndex) {
				const string& solverName = task.shared->solverNames[solverIndex];
				if(!excludeSolver(solverName)) {
					ISolver* solver = ISolverFactory::make(solverName);
					assert(solver != NULL);
					onSolverStart(ss, M, *solver);
					delete solver;
				}	
			}

			onSampleEnd(ss);

			atomic<size_t>& lock = task.shared->coutLock;
			size_t unlocked = 0;
			size_t locked = 1;

			while(!atomic_compare_exchange_weak<size_t>(&lock, &unlocked, locked)) {
				cout << ss.str();
				lock = unlocked;
			}

			ss.clear();
		}

		if (size >= 10 && inc == 1) {
			inc = 10;
		} else if (size >= 100 && inc == 10) {
			inc = 100;
		} else if (size >= 1000 && inc == 100) {
			inc = 1000;
		}
	}
} 
