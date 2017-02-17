#ifndef ISERIALIZABLEFORMAT_H
#define ISERIALIZABLEFORMAT_H

#include <iostream>

#include "Array2D.h"
#include "Assignment.h"
#include "ISerializableFormat.h"

using std::ostream;

class ISerializableFormat {
public:
	ISerializableFormat();
	~ISerializableFormat();

	virtual bool write(ostream& s, const Array2D<double>& M, const Assignment& A) const = 0;
};

#endif
