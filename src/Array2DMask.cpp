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
	initialize(numEntries, numEntries);
}

Array2DMask::Array2DMask(size_t numRows, size_t numCols) {
	initialize(numRows, numCols);
}

Array2DMask::Array2DMask(const Array2DMask& other) {
	m_rows = new ArrayMask<size_t>(*other.m_rows);
	m_cols = new ArrayMask<size_t>(*other.m_cols);
}

Array2DMask::~Array2DMask() {
	delete m_rows;
	m_rows = NULL;

	delete m_cols;
	m_cols = NULL;
}

Array2DMask::iterator Array2DMask::begin(size_t dim) {
	assert(dim < 2);

	if(dim == 0) {
		return m_rows->begin();
	}

	return m_cols->begin();
}

Array2DMask::iterator Array2DMask::end(size_t dim) {
	assert(dim < 2);

	if(dim == 0) {
		return m_rows->end();
	}

	return m_cols->end();

}

void Array2DMask::erase(size_t dim, size_t i) {
	assert(dim < 2);

	if(dim == 0) {
		m_rows->erase(i);
	} else {
		m_cols->erase(i);
	}
}

void Array2DMask::initialize(size_t numRows, size_t numCols) {
	assert(numRows > 0);
	assert(numCols > 0);

	m_rows = new ArrayMask<size_t>(numRows);
	m_cols = new ArrayMask<size_t>(numCols);
}
