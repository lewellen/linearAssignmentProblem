#ifndef IOUTPUTFORMATFACTORY_H
#define IOUTPUTFORMATFACTORY_H

#include <string>

#include "IOutputFormat.h"

using std::string;

class IOutputFormatFactory {
public:
	static const string O_FORMAT_LATEX;
	static const string O_FORMAT_LIST;
	static const string O_FORMAT_MATRIX;
	static const string O_FORMAT_TABLE;

	static bool isValidName(const string& name);
	static const string* getValidNames(size_t& numNamesOut);
	static IOutputFormat* make(const string& name);
};

#endif
