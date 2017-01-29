#ifndef ISOLVER_H
#define ISOLVER_H

#include <vector>
#include <utility>

#include "Array2D.h"

using std::vector;
using std::pair;

class ISolver {
public:
	ISolver();
	virtual ~ISolver();

	/*
	 * Finds the minimum cost for n workers to complete n tasks.
	 *
	 * @param M Each row is a worker, each column a task; Entry M[row, col]
	 * represents cost of worker row performing task col.
	 *
	 * @returns Vector of jobs by workers; v[ worker ] = job.
	 */
	virtual vector<size_t> operator() (const Array2D<double>& M) const = 0;
};

#endif
