#include <iostream>

#include "Array2D.h"
#include "Assignment.h"
#include "LatexOutputFormat.h"

using std::endl;
using std::ostream;

LatexOutputFormat::LatexOutputFormat() {

}

LatexOutputFormat::~LatexOutputFormat() {

}

bool LatexOutputFormat::write(ostream& s, const Array2D<double>& M, const Assignment& A) const {
	s << "\\begin{pmatrix}" << endl;

	for(size_t row = 0; row < M.getNumRows(); ++row) {
		size_t assignedCol = A[row];

		for(size_t col = 0; col < M.getNumCols(); ++col) {
			if(col == assignedCol) {
				s << "\\fbox{";
			}

			s << M.getEntry(row, col);

			if(col == assignedCol) {
				s << "}";
			}

			if(col + 1 != M.getNumCols()) {
				s << " & ";
			}
		}

		if(row + 1 != M.getNumRows()) {
			s << "\\\\";
		}
		s << endl;
	}

	s << "\\end{pmatrix}" << endl;

	return true;
} 
