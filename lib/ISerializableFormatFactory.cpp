#include <cassert>
#include <string>

#include "ISerializableFormat.h"
#include "ISerializableFormatFactory.h"

#include "MatrixSerializableFormat.h"
#include "TableSerializableFormat.h"
#include "ListSerializableFormat.h"

using std::string;

const string ISerializableFormatFactory::S_FORMAT_MATRIX = "MATRIX";
const string ISerializableFormatFactory::S_FORMAT_TABLE = "TABLE";
const string ISerializableFormatFactory::S_FORMAT_LIST = "LIST";

bool ISerializableFormatFactory::isValidName(const string& name) {
	return 
		(name == S_FORMAT_MATRIX) ||
		(name == S_FORMAT_TABLE) ||
		(name == S_FORMAT_LIST);
}

const string* ISerializableFormatFactory::getValidNames(size_t& numNames) {
	static size_t s_numNames = 3;
	static string s_names[] = {
		S_FORMAT_MATRIX,
		S_FORMAT_TABLE,
		S_FORMAT_LIST
	};

	numNames = s_numNames;
	return s_names;
}

ISerializableFormat* ISerializableFormatFactory::make(const string& name) {
	assert(isValidName(name));

	if(name == S_FORMAT_MATRIX) {
		return new MatrixSerializableFormat();
	}

	if(name == S_FORMAT_TABLE) {
		return new TableSerializableFormat();
	}

	if(name == S_FORMAT_LIST) {
		return new ListSerializableFormat();
	}

	return NULL;
}
