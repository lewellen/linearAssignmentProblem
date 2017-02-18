#include <iostream>

#include "Array2D.h"
#include "TableInputFormat.h"

using std::endl;
using std::istream;
using std::ostream;

TableInputFormat::TableInputFormat() {

}

TableInputFormat::~TableInputFormat() {

}

bool TableInputFormat::read(istream& s, Array2D<double>& M) const {
	size_t numRows = 0, numCols = 0;

	s >> numRows;
	s >> numCols;

	M = Array2D<double>(numRows, numCols);

	size_t entries = numRows * numCols;
	for(size_t i = 0; i < entries; ++i) {
		size_t row, col;
		double value = 0;

		s >> row;
		s >> col;
		s >> value;

		M.getEntry(row, col) = value;
	}

	return true;
}

bool TableInputFormat::write(ostream& s, Array2D<double>& M) const {
	s << M.getNumRows() << endl;
	s << M.getNumCols() << endl;

	for(size_t row = 0; row < M.getNumRows(); ++row) {
		for(size_t col = 0; col < M.getNumCols(); ++col) {
			s << row << " " << col << " " << M.getEntry(row, col) << endl;
		}
	}

	return true;
}
