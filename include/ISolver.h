#ifndef ISOLVER_H
#define ISOLVER_H

#include <list>
#include <utility>

#include "Array2D.h"

using std::list;
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
	 * @returns Worker index assigned to list's index. (First entry 
	 * corresponds to first task, second to second task, and so on.)
	 */
	virtual list<size_t> operator() (const Array2D<double>& M) const = 0;
};

#endif
