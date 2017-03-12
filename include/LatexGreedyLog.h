#ifndef LATEXGREEDYLOG_H
#define LATEXGREEDYLOG_H

#include <cstdlib>
#include <iostream>

#include "Array2D.h"
#include "Assignment.h"
#include "IGreedyLog.h"

using std::ostream;

class LatexGreedyLog : public IGreedyLog {
public:
	LatexGreedyLog(ostream& output);
	~LatexGreedyLog();

	void input(
		const Array2D<double>& M
	);

	void afterAssignment(
		const Array2D<double>& M,
		const Assignment& A,
		const size_t& row,
		const size_t& col
	);

	void output(
		const Array2D<double>& M,
		const Assignment& A
	);

private:
	ostream& m_output;
};

#endif
