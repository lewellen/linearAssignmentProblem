#include <cassert>
#include <iostream>
#include <limits>
#include <utility>

#include "ArrayMask.h"

#include "Array2DMask.h"

using std::endl;
using std::numeric_limits;
using std::ostream;
using std::pair;

Array2DMask::Array2DMask(size_t numEntries) {
	assert(numEntries > 0);
	m_numEntries = numEntries;
		
	m_rows = indexedMask(m_numEntries);
	m_cols = indexedMask(m_numEntries);

	m_matrix = new double[m_numEntries * m_numEntries];
	for(size_t row = 0; row < m_numEntries; ++row) {
		for(size_t col = 0; col < m_numEntries; ++col) {
			m_matrix[row * m_numEntries + col] = 0;
		}
	}
}

Array2DMask::~Array2DMask() {
	m_numEntries = 0;

	delete m_rows;
	m_rows = NULL;

	delete m_cols;
	m_cols = NULL;

	delete[] m_matrix;
	m_matrix = NULL;
}

Array2DMask::iterator Array2DMask::rowBegin() {
	return m_rows->begin();
}

Array2DMask::iterator Array2DMask::rowEnd() {
	return m_rows->end();
}

Array2DMask::iterator Array2DMask::colBegin() {
	return m_cols->begin();
}

Array2DMask::iterator Array2DMask::colEnd() {
	return m_cols->end();
}

double& Array2DMask::getEntry(size_t row, size_t col) {
	assert(row < m_numEntries);
	assert(col < m_numEntries);
	return m_matrix[row * m_numEntries + col];
}

const double& Array2DMask::getEntry(size_t row, size_t col) const {
	assert(row < m_numEntries);
	assert(col < m_numEntries);
	return m_matrix[row * m_numEntries + col];	
}

const size_t& Array2DMask::getNumEntries() const {
	return m_numEntries;
}

void Array2DMask::eraseRow(size_t i) {
	m_rows->erase(i);
}

void Array2DMask::eraseCol(size_t i) {
	m_cols->erase(i);
}	

pair<double, size_t> Array2DMask::getRowMin(size_t row) {
	assert(row < m_numEntries);

	double minValue = +numeric_limits<double>::infinity();
	size_t minCol = 0;

	for(ArrayMask<size_t>::iterator i = m_cols->begin(); i != m_cols->end(); ++i) {
		double value = m_matrix[row * m_numEntries + *i];
		if(value < minValue) {
			minValue = value;
			minCol = *i;
		}
	}

	return pair<double, size_t>(minValue, minCol);
}

pair<double, size_t> Array2DMask::getColMin(size_t col) {
	assert(col < m_numEntries);

	double minValue = +numeric_limits<double>::infinity();
	size_t minRow = 0;

	for(ArrayMask<size_t>::iterator i = m_rows->begin(); i != m_rows->end(); ++i) {
		double value = m_matrix[(*i) * m_numEntries + col];
		if(value < minValue) {
			minValue = value;
			minRow = *i;
		}
	}

	return pair<double, size_t>(minValue, minRow);
}

ostream& operator<< (ostream& s, Array2DMask& M) {
	for(Array2DMask::iterator row = M.rowBegin(); row != M.rowEnd(); ++row) {
		for(Array2DMask::iterator col = M.colBegin(); col != M.colEnd(); ++col) {
			s << M.getEntry(*row, *col) << " ";
		}
		s << endl;
	}
	return s;
}

ArrayMask<size_t>* Array2DMask::indexedMask(size_t numEntries) {
	ArrayMask<size_t>* mask = new ArrayMask<size_t>(numEntries);
	assert(mask != NULL);

	size_t index = 0;
	for(ArrayMask<size_t>::iterator i = mask->begin(); i != mask->end(); ++i) {
		*i = index;
		++index;
	}

	return mask;
}
