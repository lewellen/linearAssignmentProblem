#ifndef ISERIALIZABLEFORMATFACTORY_H
#define ISERIALIZABLEFORMATFACTORY_H

#include <string>

#include "ISerializableFormat.h"

using std::string;

class ISerializableFormatFactory {
public:
	static const string S_FORMAT_MATRIX;
	static const string S_FORMAT_TABLE;
	static const string S_FORMAT_LIST;

	static bool isValidName(const string& name);
	static const string* getValidNames(size_t& numNamesOut);
	static ISerializableFormat* make(const string& name);
};

#endif
