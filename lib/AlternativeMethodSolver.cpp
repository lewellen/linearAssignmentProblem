#include <cassert>
#include <limits>
#include <map>
#include <set>

#include "Array2D.h"
#include "Array2DMask.h"
#include "Assignment.h"
#include "ISolver.h"
#include "AlternativeMethodSolver.h"

using std::map;
using std::numeric_limits;
using std::set;

AlternativeMethodSolver::AlternativeMethodSolver() {

}

AlternativeMethodSolver::~AlternativeMethodSolver() {

}

Assignment AlternativeMethodSolver::operator() (const Array2D<double>& A) const {
	assert(A.getNumRows() == A.getNumCols());
	// http://shodhganga.inflibnet.ac.in/bitstream/10603/3970/10/10_chapter%205.pdf

	Assignment assignments(A.getNumRows());

	Array2D<double> B = A;
	Array2DMask M(B.getNumRows(), B.getNumCols());

	map< size_t, set<size_t> > jobByWorker;
	for(Array2DMask::iterator row = M.begin(0); row != M.end(0); ++row) {
		double rowMin = numeric_limits<double>::infinity();
		size_t rowMinColIndex = 0;
		for(Array2DMask::iterator col = M.begin(1); col != M.end(1); ++col) {
			double cost = B.getEntry(*row, *col);
			if(rowMin > cost) {
				jobByWorker[ *row ].clear();
				rowMin = cost;
			}

			if(rowMin == cost) {
				jobByWorker[ *row ].insert( *col );
			}
		}
	}

	map< size_t, set<size_t> > workerByJob;

	for(map< size_t, set<size_t> >::const_iterator i = jobByWorker.begin(); i != jobByWorker.end(); ++i) {
		const set<size_t>& job = (*i).second;
		for(set<size_t>::const_iterator j = job.begin(); j != job.end(); ++j) {
			workerByJob[ *j ].insert( (*i).first );
		}
	}

	for(map<size_t, set<size_t> >::const_iterator i = workerByJob.begin(); i != workerByJob.end(); ++i) {
		size_t job = (*i).first;
		const set<size_t>& workers = (*i).second;

		if(workers.size() == 1) {
			size_t worker = (*workers.begin());
			M.erase(0, worker);
			M.erase(1, job);
			assignments[ worker ] = job;

			jobByWorker.erase(worker);
			workerByJob.erase(job);
		}
	}

	return assignments;
}

