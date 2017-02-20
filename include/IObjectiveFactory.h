#ifndef IOBJECTIVEFACTORY_H
#define IOBJECTIVEFACTORY_H

#include <string>

#include "IObjective.h"

using std::string;

class IObjectiveFactory {
public:
	static const string OBJECTIVE_MINIMIZE;
	static const string OBJECTIVE_MAXIMIZE;

	static bool isValidName(const string& name);
	static const string* getValidNames(size_t& numNamesOut);
	static IObjective* make(const string& name);
};

#endif
