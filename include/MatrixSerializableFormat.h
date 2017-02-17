#ifndef MATRIXSERIALIZABLEFORMAT_H
#define MATRIXSERIALIZABLEFORMAT_H

#include <iostream>

#include "Array2D.h"
#include "Assignment.h"
#include "ISerializableFormat.h"

using std::ostream;

class MatrixSerializableFormat : public ISerializableFormat {
public:
	MatrixSerializableFormat();
	~MatrixSerializableFormat();

	bool write(ostream& s, const Array2D<double>& M, const Assignment& A) const;
};

#endif
