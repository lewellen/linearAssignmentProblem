#include <list>
#include <utility>

#include "CostMatrix.h"
#include "ISolver.h"
#include "AlternativeMethodSolver.h"

using std::list;
using std::pair;

AlternativeMethodSolver::AlternativeMethodSolver() {

}

AlternativeMethodSolver::~AlternativeMethodSolver() {

}

list< pair<size_t, size_t> > AlternativeMethodSolver::operator() (CostMatrix& M) {
	list< pair<size_t, size_t> > assignments;

	return assignments;
}


