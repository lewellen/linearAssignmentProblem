#include <iostream>

#include "Array2D.h"
#include "Assignment.h"
#include "TableOutputFormat.h"

using std::endl;
using std::ostream;

TableOutputFormat::TableOutputFormat() {

}

TableOutputFormat::~TableOutputFormat() {

}

bool TableOutputFormat::write(ostream& s, const Array2D<double>& M, const Assignment& A) const {
	for(size_t i = 0; i < A.size(); ++i) {
		s << i << " " << A[i] << " " << M.getEntry(i, A[i]) << endl;
	}
	return true;
} 
