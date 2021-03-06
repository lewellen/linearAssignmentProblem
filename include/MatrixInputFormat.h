#ifndef MATRIXINPUTFORMAT_H
#define MATRIXINPUTFORMAT_H

#include <iostream>

#include "Array2D.h"
#include "IInputFormat.h"

using std::istream;
using std::ostream;

class MatrixInputFormat : public IInputFormat {
public:
	MatrixInputFormat();
	virtual ~MatrixInputFormat();

	bool read(istream& s, Array2D<double>& M) const;
	bool write(ostream& s, Array2D<double>& M) const;
};

#endif
