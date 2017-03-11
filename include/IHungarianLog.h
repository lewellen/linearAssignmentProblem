#ifndef IHUNGARIANLOG_H
#define IHUNGARIANLOG_H

#include <cstdlib>
#include <list>
#include <utility>

#include "Array2D.h"
#include "Assignment.h"

using std::list;
using std::pair;

class IHungarianLog {
public:
	IHungarianLog();
	virtual ~IHungarianLog();

	virtual void input(
		const Array2D<double>& M
	) = 0;

	virtual void afterDeductRowAndColMin(
		const Array2D<double>& M
	) = 0;

	virtual void afterInitAssignment(
		const Array2D<double>& M, 
		const size_t* rowsStarredCol, 
		const bool* colCovered
	) = 0;

	virtual void afterStep1(
		const Array2D<double>& M,
		const size_t* rowsStarredCol,
		const bool* colCovered,
		const bool* rowCovered,
		const size_t* rowsPrimedCol
	) = 0;
	 
	virtual void beforeStep2(
		const Array2D<double>& M,
		const size_t* rowsStarredCol,
		const bool* colCovered,
		const bool* rowCovered,
		const size_t* rowsPrimedCol,
		const list< pair<size_t, size_t> >& starred,
		const list< pair<size_t, size_t> >& primed
	) = 0;

	virtual void afterDeductUncoveredMin(
		const Array2D<double>& M,
		const size_t* rowsStarredCol,
		const bool* colCovered,
		const bool* rowCovered,
		const size_t* rowsPrimedCol,
		const double& minValue
	) = 0;

	virtual void output(
		const Array2D<double>& M,
		const Assignment& A
	) = 0;
};

#endif
