#ifndef ARRAY2DMASK_H
#define ARRAY2DMASK_H

#include <iostream>
#include <utility>

#include "ArrayMask.h"

using std::ostream;
using std::pair;

class Array2DMask {
public:
	typedef ArrayMask<size_t>::iterator iterator;
	
	Array2DMask(size_t numEntries);
	Array2DMask(size_t numRows, size_t numCols);
	Array2DMask(const Array2DMask& other);
	~Array2DMask();

	iterator begin(size_t dimension);
	iterator end(size_t dimension);

	void erase(size_t dimension, size_t i);

	pair<double, size_t> getDimensionMin(size_t dimension, size_t row);

private:
	ArrayMask<size_t>* m_rows;
	ArrayMask<size_t>* m_cols;

	void initialize(size_t rows, size_t columns);	
	ArrayMask<size_t>* indexedMask(size_t numEntries);
};

#endif
