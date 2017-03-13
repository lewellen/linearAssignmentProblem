#include <cassert>

#include "ISolver.h"
#include "ISolverFactory.h"

#include "AtRandomSolver.h"
#include "BruteSolver.h"
#include "EfficientGreedySolver.h"
#include "HungarianMethodSolver.h"
#include "NaiveGreedySolver.h"

const string ISolverFactory::SOLVER_ATRANDOM = "RANDOM";
const string ISolverFactory::SOLVER_BRUTE = "BRUTE";
const string ISolverFactory::SOLVER_GREEDY_EFFICIENT = "GREEDY-EFFICIENT";
const string ISolverFactory::SOLVER_GREEDY_NAIVE = "GREEDY-NAIVE";
const string ISolverFactory::SOLVER_HUNGARIAN = "HUNGARIAN";

bool ISolverFactory::isValidName(const string& name) {
	return 
		(name == SOLVER_ATRANDOM) ||
		(name == SOLVER_BRUTE) ||
		(name == SOLVER_GREEDY_EFFICIENT) || 
		(name == SOLVER_GREEDY_NAIVE) || 
		(name == SOLVER_HUNGARIAN);
}

const string* ISolverFactory::getValidNames(size_t& numNames) {
	static size_t s_numNames = 5;
	static string s_names[] = {
		SOLVER_ATRANDOM,
		SOLVER_BRUTE,
		SOLVER_GREEDY_EFFICIENT,
		SOLVER_GREEDY_NAIVE,
		SOLVER_HUNGARIAN
	};

	numNames = s_numNames;
	return s_names;
}

ISolver* ISolverFactory::make(const string& name) {
	assert(isValidName(name));

	if(name == SOLVER_ATRANDOM) {
		return new AtRandomSolver();
	}

	if(name == SOLVER_BRUTE) {
		return new BruteSolver();
	}

	if(name == SOLVER_GREEDY_EFFICIENT) {
		return new EfficientGreedySolver();
	}

	if(name == SOLVER_GREEDY_NAIVE) {
		return new NaiveGreedySolver();
	}

	if(name == SOLVER_HUNGARIAN) {
		return new HungarianMethodSolver();
	}

	return NULL;
}
