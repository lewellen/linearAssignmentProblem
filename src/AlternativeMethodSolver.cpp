#include <cassert>
#include <list>
#include <utility>

#include "Array2D.h"
#include "Array2DMask.h"
#include "ISolver.h"
#include "AlternativeMethodSolver.h"

using std::list;
using std::pair;

AlternativeMethodSolver::AlternativeMethodSolver() {

}

AlternativeMethodSolver::~AlternativeMethodSolver() {

}

list<size_t> AlternativeMethodSolver::operator() (const Array2D<double>& A) const {
	assert(A.getNumRows() == A.getNumCols());
	// http://shodhganga.inflibnet.ac.in/bitstream/10603/3970/10/10_chapter%205.pdf

	list<size_t> assignments;

	Array2D<double> B = A;
	Array2DMask M(B.getNumRows(), B.getNumCols());

	return assignments;
}

