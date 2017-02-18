#ifndef IINPUTFORMATFACTORY_H
#define IINPUTFORMATFACTORY_H

#include <string>

#include "IInputFormat.h"

using std::string;

class IInputFormatFactory {
public:
	static const string I_FORMAT_MATRIX;
	static const string I_FORMAT_TABLE;

	static bool isValidName(const string& name);
	static const string* getValidNames(size_t& numNamesOut);
	static IInputFormat* make(const string& name);
};

#endif
