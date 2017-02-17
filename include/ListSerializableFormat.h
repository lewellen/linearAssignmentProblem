#ifndef LISTSERIALIZABLEFORMAT_H
#define LISTSERIALIZABLEFORMAT_H

#include <iostream>

#include "Array2D.h"
#include "Assignment.h"
#include "ISerializableFormat.h"

using std::ostream;

class ListSerializableFormat : public ISerializableFormat {
public:
	ListSerializableFormat();
	~ListSerializableFormat();

	bool write(ostream& s, const Array2D<double>& M, const Assignment& A) const;
};

#endif
