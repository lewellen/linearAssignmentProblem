#ifndef COSTMATRIX_H
#define COSTMATRIX_H

#include <iostream>
#include <utility>

#include "ArrayView.h"

using std::ostream;
using std::pair;

class CostMatrix {
public:
	typedef ArrayView<size_t>::iterator iterator;
	
	CostMatrix(size_t numEntries);
	~CostMatrix();

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

	friend ostream& operator<< (ostream& s, CostMatrix& M);

private:
	size_t m_numEntries;

	ArrayView<size_t>* m_rows;
	ArrayView<size_t>* m_cols;
	double* m_matrix;

	ArrayView<size_t>* indexedView(size_t numEntries);
};



#endif
