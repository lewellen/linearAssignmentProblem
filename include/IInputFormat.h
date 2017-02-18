#ifndef IINPUTFORMAT_H
#define IINPUTFORMAT_H

#include <iostream>

#include "Array2D.h"

using std::istream;
using std::ostream;

class IInputFormat {
public:
	IInputFormat();
	virtual ~IInputFormat();

	virtual bool read(istream& s, Array2D<double>& M) const = 0;
	virtual bool write(ostream& s, Array2D<double>& M) const = 0;
};

#endif
