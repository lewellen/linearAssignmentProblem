#include <iostream>

#include "Array2D.h"
#include "MatrixInputFormat.h"

using std::istream;

MatrixInputFormat::MatrixInputFormat() {

}

MatrixInputFormat::~MatrixInputFormat() {

}

bool MatrixInputFormat::read(istream& s, Array2D<double>& M) const {
	return false;
}
