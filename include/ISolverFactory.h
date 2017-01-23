#ifndef ISOLVERFACTORY_H
#define ISOLVERFACTORY_H

#include <string>

using std::string;

class ISolverFactory {
public:
	static const string SOLVER_ALTERNATIVE;
	static const string SOLVER_BRUTE;
	static const string SOLVER_HUNGARIAN;

	static bool isValidName(const string& name);
	static ISolver* make(const string& name);
};

#endif
