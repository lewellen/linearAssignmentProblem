#include <cstdlib>
#include <iostream>
#include <vector>

#include "Array2D.h"
#include "Assignment.h"

using std::endl;
using std::ostream;
using std::vector;

Assignment::Assignment(size_t numWorkers) {
	m_size = numWorkers;
	m_v.reserve(numWorkers);
}

Assignment::Assignment(const Assignment& other) {
	m_size = other.m_size;
	for(size_t i = 0; i < m_size; ++i) {
		m_v[i] = other.m_v[i];
	}
}

Assignment& Assignment::operator= (const Assignment& other) {
	m_size = other.m_size;
	for(size_t i = 0; i < m_size; ++i) {
		m_v[i] = other.m_v[i];
	}

	return *this;
}

Assignment::~Assignment() {

}

double Assignment::cost(const Array2D<double>& M) const {
	double cost = 0.0;
	for(size_t worker = 0; worker < m_size; ++worker) {
		cost += M.getEntry( worker, m_v[worker] );
	}
	return cost;
}

ostream& Assignment::display(ostream& s, const Array2D<double>& M) const {
	for(size_t row = 0; row < M.getNumRows(); ++row) {
		size_t assignedCol = m_v[row];

		for(size_t col = 0; col < M.getNumCols(); ++col) {
			if(col == assignedCol) {
				s << "[";
			} else {
				s << " ";
			}

			s << M.getEntry(row, col);

			if(col == assignedCol) {
				s << "]";
			} else {
				s << " ";
			}

			s << " ";
		}

		s << endl;
	}

	return s;
}

size_t Assignment::size() const {
	return m_size;
}

size_t& Assignment::operator[] (size_t index) {
	return m_v[index];
}

const size_t& Assignment::operator[] (size_t index) const {
	return m_v[index];
}

ostream& operator<< (ostream& s, const Assignment& a) {
	s << "[";
	for(size_t i = 0; i < a.m_size; ++i) {
		s << a.m_v[i];
		if(i + 1 < a.m_size) {
			s << ", ";
		}
	}
	s << "]";

	return s;
}