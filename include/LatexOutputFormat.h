#ifndef LATEXOUTPUTFORMAT_H
#define LATEXOUTPUTFORMAT_H

#include <iostream>

#include "Array2D.h"
#include "Assignment.h"
#include "IOutputFormat.h"

using std::ostream;

class LatexOutputFormat : public IOutputFormat {
public:
	LatexOutputFormat();
	virtual ~LatexOutputFormat();

	bool write(ostream& s, const Array2D<double>& M, const Assignment& A) const;
};

#endif
