#ifndef MATRIXOUTPUTFORMAT_H
#define MATRIXOUTPUTFORMAT_H

#include <iostream>

#include "Array2D.h"
#include "Assignment.h"
#include "IOutputFormat.h"

using std::ostream;

class MatrixOutputFormat : public IOutputFormat {
public:
	MatrixOutputFormat();
	~MatrixOutputFormat();

	bool write(ostream& s, const Array2D<double>& M, const Assignment& A) const;
};

#endif
