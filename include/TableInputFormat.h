#ifndef TABLEINPUTFORMAT_H
#define TABLEINPUTFORMAT_H

#include <iostream>

#include "Array2D.h"
#include "IInputFormat.h"

using std::istream;
using std::ostream;

class TableInputFormat : public IInputFormat {
public:
	TableInputFormat();
	virtual ~TableInputFormat();

	bool read(istream& s, Array2D<double>& M) const;
	bool write(ostream& s, Array2D<double>& M) const;
};

#endif
