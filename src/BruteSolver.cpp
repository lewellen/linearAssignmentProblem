#include <limits>
#include <list>
#include <utility>

#include "CostMatrix.h"
#include "ISolver.h"
#include "BruteSolver.h"

using std::list;
using std::numeric_limits;
using std::pair;

BruteSolver::BruteSolver() {

}

BruteSolver::~BruteSolver() {

}

list<size_t> BruteSolver::operator() (CostMatrix& M) {
	list<size_t> workers;
	for(size_t i = 0; i < M.getNumEntries(); ++i) {
		workers.push_back(i);
	}
	
	list<size_t> workingList;

	double minCost = numeric_limits<double>::infinity();
	list<size_t> minAssign;

	permutation(workers, workingList, M, minCost, minAssign);

	workers.clear();

	return minAssign;
}

void BruteSolver::permutation(
	list<size_t>& A, list<size_t>& B, 
	CostMatrix& M, double& minCost, list<size_t>& minAssign) {

	if(A.empty()) {
		double cost = 0.0;
		size_t job = 0;
		for(list<size_t>::iterator i = B.begin(); i != B.end(); ++i) {
			cost += M.getEntry(*i, job++);
		}

		if(cost < minCost) {
			minCost = cost;
			minAssign = B;
		}
		return;
	}

	for(list<size_t>::iterator i = A.begin(); i != A.end(); ++i) {
		size_t a = *i;
		i = A.erase(i);
		B.push_back(a);
		permutation(A, B, M, minCost, minAssign);
		B.erase(--B.end());
		i = A.insert(i, a);
	}
}
