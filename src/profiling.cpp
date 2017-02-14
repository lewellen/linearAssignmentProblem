#include <cstdlib>
#include <iostream>
#include <list>
#include <utility>

#include <sys/time.h>

#include "Array2D.h"
#include "ISolver.h"
#include "ISolverFactory.h"

using std::cout;
using std::endl;
using std::list;
using std::pair;

typedef Array2D<double> CostMatrix;

class Stopwatch {
public:
	Stopwatch() {

	}

	~Stopwatch() {

	}

	void start() {
		gettimeofday(&m_start, NULL);
	}

	void stop() {
		gettimeofday(&m_stop, NULL);
	}

	double elapsedMs() const {
		return (m_stop.tv_sec - m_start.tv_sec) * 1e3 + (m_stop.tv_usec - m_start.tv_usec) * 1e-3;
	}

private:
	timeval m_start;
	timeval m_stop;
};

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

void displayAssignment(const CostMatrix& M, const vector<size_t>& jobsByWorker) {
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

}

int main(int argc, char** argv) {
	ISolver* solver = ISolverFactory::make(ISolverFactory::SOLVER_BRUTE);
	assert(solver != NULL);

	Stopwatch S;
	cout << "N\telapsed (sec)" << endl;
	for(size_t size = 2; size <= 12; ++size) {
		CostMatrix M = randomMatrix(size);
		S.start();
		vector<size_t> jobsByWorker = (*solver)(M);
		S.stop();

		cout << size << "\t" << S.elapsedMs() << endl;
	}

	delete solver;	

	return EXIT_SUCCESS;
}
