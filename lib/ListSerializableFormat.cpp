#include <iostream>

#include "Array2D.h"
#include "Assignment.h"
#include "ListSerializableFormat.h"

using std::endl;
using std::ostream;

ListSerializableFormat::ListSerializableFormat() {

}

ListSerializableFormat::~ListSerializableFormat() {

}

bool ListSerializableFormat::write(ostream& s, const Array2D<double>& M, const Assignment& A) const {
	for(size_t i = 0; i < A.size() - 1; ++i) {
		s << A[i] << ", ";
	}

	if(A.size() > 0) {
		s << A[A.size() - 1];
	}

	s << endl;

	return s;
} 
