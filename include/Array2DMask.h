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
	~Array2DMask();

	iterator rowBegin();
	iterator rowEnd();

	iterator colBegin();
	iterator colEnd();

	double& getEntry(size_t row, size_t col);
	const double& getEntry(size_t row, size_t col) const;

	const size_t& getNumEntries() const;

	void eraseRow(size_t i);
	void eraseCol(size_t i);

	pair<double, size_t> getRowMin(size_t row);
	pair<double, size_t> getColMin(size_t col);

	friend ostream& operator<< (ostream& s, Array2DMask& M);

private:
	size_t m_numEntries;

	ArrayMask<size_t>* m_rows;
	ArrayMask<size_t>* m_cols;
	double* m_matrix;

	ArrayMask<size_t>* indexedMask(size_t numEntries);
};

#endif
