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

list<size_t> AlternativeMethodSolver::operator() (CostMatrix& M) {
	list<size_t> assignments;

	return assignments;
}


