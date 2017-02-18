#ifndef IOUTPUTFORMATFACTORY_H
#define IOUTPUTFORMATFACTORY_H

#include <string>

#include "IOutputFormat.h"

using std::string;

class IOutputFormatFactory {
public:
	static const string S_FORMAT_MATRIX;
	static const string S_FORMAT_TABLE;
	static const string S_FORMAT_LIST;

	static bool isValidName(const string& name);
	static const string* getValidNames(size_t& numNamesOut);
	static IOutputFormat* make(const string& name);
};

#endif
