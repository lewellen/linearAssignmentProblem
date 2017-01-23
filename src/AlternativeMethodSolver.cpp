#include <list>
#include <utility>

#include "Array2DMask.h"
#include "ISolver.h"
#include "AlternativeMethodSolver.h"

using std::list;
using std::pair;

AlternativeMethodSolver::AlternativeMethodSolver() {

}

AlternativeMethodSolver::~AlternativeMethodSolver() {

}

list<size_t> AlternativeMethodSolver::operator() (Array2DMask& M) {
	list<size_t> assignments;

	Array2DMask N(M.getNumEntries());
	for(size_t i = 0; i < M.getNumEntries(); ++i) {
		for(size_t j = 0; j < M.getNumEntries(); ++j) {
			N.getEntry(i,j) = M.getEntry(i,j);
		}
	}

	return assignments;
}

