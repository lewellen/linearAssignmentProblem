#ifndef ISOLVER_H
#define ISOLVER_H

#include "Array2D.h"
#include "Assignment.h"

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
	virtual Assignment operator() (const Array2D<double>& M) const = 0;
};

#endif
