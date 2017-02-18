#ifndef LISTOUTPUTFORMAT_H
#define LISTOUTPUTFORMAT_H

#include <iostream>

#include "Array2D.h"
#include "Assignment.h"
#include "IOutputFormat.h"

using std::ostream;

class ListOutputFormat : public IOutputFormat {
public:
	ListOutputFormat();
	~ListOutputFormat();

	bool write(ostream& s, const Array2D<double>& M, const Assignment& A) const;
};

#endif
