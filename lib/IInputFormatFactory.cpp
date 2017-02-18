#include <cassert>
#include <string>

#include "IInputFormat.h"
#include "IInputFormatFactory.h"

#include "MatrixInputFormat.h"
#include "TableInputFormat.h"

using std::string;

const string IInputFormatFactory::I_FORMAT_MATRIX = "MATRIX";
const string IInputFormatFactory::I_FORMAT_TABLE = "TABLE";

bool IInputFormatFactory::isValidName(const string& name) {
	return 
		(name == I_FORMAT_MATRIX) ||
		(name == I_FORMAT_TABLE);
}

const string* IInputFormatFactory::getValidNames(size_t& numNames) {
	static size_t s_numNames = 2;
	static string s_names[] = {
		I_FORMAT_MATRIX,
		I_FORMAT_TABLE
	};

	numNames = s_numNames;
	return s_names;
}

IInputFormat* IInputFormatFactory::make(const string& name) {
	assert(isValidName(name));

	if(name == I_FORMAT_MATRIX) {
		return new MatrixInputFormat();
	}

	if(name == I_FORMAT_TABLE) {
		return new TableInputFormat();
	}

	return NULL;
}
