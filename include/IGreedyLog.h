#ifndef IGREEDYLOG_H
#define IGREEDYLOG_H

#include <cstdlib>

#include "Array2D.h"
#include "Assignment.h"

class IGreedyLog {
public:
	IGreedyLog();
	virtual ~IGreedyLog();

	virtual void input(
		const Array2D<double>& M
	) = 0;

	virtual void afterAssignment(
		const Array2D<double>& M,
		const Assignment& A,
		const size_t& row,
		const size_t& col
	) = 0;

	virtual void output(
		const Array2D<double>& M,
		const Assignment& A
	) = 0;
};

#endif
