#include <cassert>

#include "IObjective.h"
#include "IObjectiveFactory.h"

#include "MinimizeObjective.h"
#include "MaximizeObjective.h"

const string IObjectiveFactory::OBJECTIVE_MINIMIZE = "MINIMIZE";
const string IObjectiveFactory::OBJECTIVE_MAXIMIZE = "MAXIMIZE";

bool IObjectiveFactory::isValidName(const string& name) {
	return 
		(name == OBJECTIVE_MINIMIZE) ||
		(name == OBJECTIVE_MAXIMIZE);
}

const string* IObjectiveFactory::getValidNames(size_t& numNames) {
	static size_t s_numNames = 2;
	static string s_names[] = {
		OBJECTIVE_MINIMIZE,
		OBJECTIVE_MAXIMIZE
	};

	numNames = s_numNames;
	return s_names;
}

IObjective* IObjectiveFactory::make(const string& name) {
	assert(isValidName(name));

	if(name == OBJECTIVE_MINIMIZE) {
		return new MinimizeObjective();
	}

	if(name == OBJECTIVE_MAXIMIZE) {
		return new MaximizeObjective();
	}

	return NULL;
}
