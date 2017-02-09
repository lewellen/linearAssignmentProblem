#ifndef ARRAY2DMASK_H
#define ARRAY2DMASK_H

#include <iostream>
#include <utility>

#include "ArrayMask.h"

using std::ostream;
using std::pair;

class Array2DMask {
public:
	typedef ArrayMask::iterator iterator;
	
	Array2DMask(size_t numEntries);
	Array2DMask(size_t numRows, size_t numCols);
	Array2DMask(const Array2DMask& other);
	~Array2DMask();

	iterator begin(size_t dimension);
	iterator end(size_t dimension);

	void erase(size_t dimension, size_t i);

private:
	ArrayMask* m_rows;
	ArrayMask* m_cols;

	void initialize(size_t rows, size_t columns);	
};

#endif
