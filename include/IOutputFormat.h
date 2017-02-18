#ifndef IOUTPUTFORMAT_H
#define IOUTPUTFORMAT_H

#include <iostream>

#include "Array2D.h"
#include "Assignment.h"

using std::ostream;

class IOutputFormat {
public:
	IOutputFormat();
	~IOutputFormat();

	virtual bool write(ostream& s, const Array2D<double>& M, const Assignment& A) const = 0;
};

#endif
