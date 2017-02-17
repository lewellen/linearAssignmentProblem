#include <iostream>

#include "Array2D.h"
#include "Assignment.h"
#include "MatrixSerializableFormat.h"

using std::endl;
using std::ostream;

MatrixSerializableFormat::MatrixSerializableFormat() {

}

MatrixSerializableFormat::~MatrixSerializableFormat() {

}

bool MatrixSerializableFormat::write(ostream& s, const Array2D<double>& M, const Assignment& A) const {
	for(size_t row = 0; row < M.getNumRows(); ++row) {
		size_t assignedCol = A[row];

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
