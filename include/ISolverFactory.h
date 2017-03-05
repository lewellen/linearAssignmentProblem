#ifndef ISOLVERFACTORY_H
#define ISOLVERFACTORY_H

#include <string>

#include "ISolver.h"

using std::string;

class ISolverFactory {
public:
	static const string SOLVER_ALTERNATIVE;
	static const string SOLVER_ATRANDOM;
	static const string SOLVER_BRUTE;
	static const string SOLVER_GREEDY_EFFICIENT;
	static const string SOLVER_GREEDY_NAIVE;
	static const string SOLVER_HUNGARIAN;

	static bool isValidName(const string& name);
	static const string* getValidNames(size_t& numNamesOut);
	static ISolver* make(const string& name);
};

#endif
