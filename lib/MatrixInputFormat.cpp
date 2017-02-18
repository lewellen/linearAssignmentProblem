#include <iostream>

#include "Array2D.h"
#include "MatrixInputFormat.h"

using std::istream;

MatrixInputFormat::MatrixInputFormat() {

}

MatrixInputFormat::~MatrixInputFormat() {

}

bool MatrixInputFormat::read(istream& s, Array2D<double>& M) const {
	size_t numRows = 0, numCols = 0;
	s >> numRows;
	s >> numCols;

	M = Array2D<double>(numRows, numCols);

	for(size_t row = 0; row < numRows; ++row) {
		for(size_t col = 0; col < numCols; ++col) {
			double value = 0;
			s >> value;
			M.getEntry(row, col) = value;
		}
	}

	return true;
}
