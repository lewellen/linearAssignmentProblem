#ifndef TABLEOUTPUTFORMAT_H
#define TABLEOUTPUTFORMAT_H

#include <iostream>

#include "Array2D.h"
#include "Assignment.h"
#include "IOutputFormat.h"

using std::ostream;

class TableOutputFormat : public IOutputFormat {
public:
	TableOutputFormat();
	~TableOutputFormat();

	bool write(ostream& s, const Array2D<double>& M, const Assignment& A) const;
};

#endif
