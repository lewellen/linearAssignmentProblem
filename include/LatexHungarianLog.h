#ifndef LATEXHUNGARIANLOG_H
#define LATEXHUNGARIANLOG_H

#include <cstdlib>
#include <iostream>
#include <list>
#include <utility>

#include "Array2D.h"
#include "Assignment.h"
#include "IHungarianLog.h"

using std::list;
using std::ostream;
using std::pair;

class LatexHungarianLog : public IHungarianLog {
public:
	LatexHungarianLog(ostream& output);
	~LatexHungarianLog();

	void input(
		const Array2D<double>& M
	); 

	void afterDeductRowAndColMin(
		const Array2D<double>& M
	);

	void afterInitAssignment(
		const Array2D<double>& M, 
		const size_t* rowsStarredCol, 
		const bool* colCovered
	);

	void afterStep1(
		const Array2D<double>& M,
		const size_t* rowsStarredCol,
		const bool* colCovered,
		const bool* rowCovered,
		const size_t* rowsPrimedCol
	);
	 
	void beforeStep2(
		const Array2D<double>& M,
		const size_t* rowsStarredCol,
		const bool* colCovered,
		const bool* rowCovered,
		const size_t* rowsPrimedCol,
		const list< pair<size_t, size_t> >& starred,
		const list< pair<size_t, size_t> >& primed
	);

	void afterDeductUncoveredMin(
		const Array2D<double>& M,
		const size_t* rowsStarredCol,
		const bool* colCovered,
		const bool* rowCovered,
		const size_t* rowsPrimedCol,
		const double& minValue
	);

	void output(
		const Array2D<double>& M,
		const Assignment& A
	);

private:
	ostream& m_output;
};

#endif
