#include <iostream>

#include "Array2D.h"
#include "Assignment.h"
#include "TableSerializableFormat.h"

using std::endl;
using std::ostream;

TableSerializableFormat::TableSerializableFormat() {

}

TableSerializableFormat::~TableSerializableFormat() {

}

bool TableSerializableFormat::write(ostream& s, const Array2D<double>& M, const Assignment& A) const {
	for(size_t i = 0; i < A.size(); ++i) {
		s << i << " " << A[i] << " " << M.getEntry(i, A[i]) << endl;
	}
	return s;
} 
