#ifndef TABLESERIALIZABLEFORMAT_H
#define TABLESERIALIZABLEFORMAT_H

#include <iostream>

#include "Array2D.h"
#include "Assignment.h"
#include "ISerializableFormat.h"

using std::ostream;

class TableSerializableFormat : public ISerializableFormat {
public:
	TableSerializableFormat();
	~TableSerializableFormat();

	bool write(ostream& s, const Array2D<double>& M, const Assignment& A) const;
};

#endif
