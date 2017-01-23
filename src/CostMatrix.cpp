#include <cassert>
#include <iostream>
#include <limits>
#include <utility>

#include "ArrayView.h"

#include "CostMatrix.h"

using std::endl;
using std::numeric_limits;
using std::ostream;
using std::pair;

CostMatrix::CostMatrix(size_t numEntries) {
	assert(numEntries > 0);
	m_numEntries = numEntries;
		
	m_rows = indexedView(m_numEntries);
	m_cols = indexedView(m_numEntries);

	m_matrix = new double[m_numEntries * m_numEntries];
	for(size_t row = 0; row < m_numEntries; ++row) {
		for(size_t col = 0; col < m_numEntries; ++col) {
			m_matrix[row * m_numEntries + col] = 0;
		}
	}
}

CostMatrix::~CostMatrix() {
	m_numEntries = 0;

	delete m_rows;
	m_rows = NULL;

	delete m_cols;
	m_cols = NULL;

	delete[] m_matrix;
	m_matrix = NULL;
}

CostMatrix::iterator CostMatrix::rowBegin() {
	return m_rows->begin();
}

CostMatrix::iterator CostMatrix::rowEnd() {
	return m_rows->end();
}

CostMatrix::iterator CostMatrix::colBegin() {
	return m_cols->begin();
}

CostMatrix::iterator CostMatrix::colEnd() {
	return m_cols->end();
}

double& CostMatrix::getEntry(size_t row, size_t col) {
	assert(row < m_numEntries);
	assert(col < m_numEntries);
	return m_matrix[row * m_numEntries + col];
}

const double& CostMatrix::getEntry(size_t row, size_t col) const {
	assert(row < m_numEntries);
	assert(col < m_numEntries);
	return m_matrix[row * m_numEntries + col];	
}

const size_t& CostMatrix::getNumEntries() const {
	return m_numEntries;
}

void CostMatrix::eraseRow(size_t i) {
	m_rows->erase(i);
}

void CostMatrix::eraseCol(size_t i) {
	m_cols->erase(i);
}	

pair<double, size_t> CostMatrix::getRowMin(size_t row) {
	assert(row < m_numEntries);

	double minValue = +numeric_limits<double>::infinity();
	size_t minCol = 0;

	for(ArrayView<size_t>::iterator i = m_cols->begin(); i != m_cols->end(); ++i) {
		double value = m_matrix[row * m_numEntries + *i];
		if(value < minValue) {
			minValue = value;
			minCol = *i;
		}
	}

	return pair<double, size_t>(minValue, minCol);
}

pair<double, size_t> CostMatrix::getColMin(size_t col) {
	assert(col < m_numEntries);

	double minValue = +numeric_limits<double>::infinity();
	size_t minRow = 0;

	for(ArrayView<size_t>::iterator i = m_rows->begin(); i != m_rows->end(); ++i) {
		double value = m_matrix[(*i) * m_numEntries + col];
		if(value < minValue) {
			minValue = value;
			minRow = *i;
		}
	}

	return pair<double, size_t>(minValue, minRow);
}

ostream& operator<< (ostream& s, CostMatrix& M) {
	for(CostMatrix::iterator row = M.rowBegin(); row != M.rowEnd(); ++row) {
		for(CostMatrix::iterator col = M.colBegin(); col != M.colEnd(); ++col) {
			s << M.getEntry(*row, *col) << " ";
		}
		s << endl;
	}
	return s;
}

ArrayView<size_t>* CostMatrix::indexedView(size_t numEntries) {
	ArrayView<size_t>* view = new ArrayView<size_t>(numEntries);
	assert(view != NULL);

	size_t index = 0;
	for(ArrayView<size_t>::iterator i = view->begin(); i != view->end(); ++i) {
		*i = index;
		++index;
	}

	return view;
}
