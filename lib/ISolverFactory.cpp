#include <cassert>

#include "ISolver.h"
#include "ISolverFactory.h"

#include "AlternativeMethodSolver.h"
#include "BruteSolver.h"
#include "HungarianMethodSolver.h"

const string ISolverFactory::SOLVER_ALTERNATIVE = "ALTERNATIVE";
const string ISolverFactory::SOLVER_BRUTE = "BRUTE";
const string ISolverFactory::SOLVER_HUNGARIAN = "HUNGARIAN";

bool ISolverFactory::isValidName(const string& name) {
	return 
		(name == SOLVER_ALTERNATIVE) ||
		(name == SOLVER_BRUTE) ||
		(name == SOLVER_HUNGARIAN);
}

const string* ISolverFactory::getValidNames(size_t& numNames) {
	static size_t s_numNames = 3;
	static string s_names[] = {
		SOLVER_ALTERNATIVE,
		SOLVER_BRUTE,
		SOLVER_HUNGARIAN
	};

	numNames = s_numNames;
	return s_names;
}

ISolver* ISolverFactory::make(const string& name) {
	assert(isValidName(name));

	if(name == SOLVER_ALTERNATIVE) {
		return new AlternativeMethodSolver();
	}

	if(name == SOLVER_BRUTE) {
		return new BruteSolver();
	}

	if(name == SOLVER_HUNGARIAN) {
		return new HungarianMethodSolver();
	}

	return NULL;
}
