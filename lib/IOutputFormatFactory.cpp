#include <cassert>
#include <string>

#include "IOutputFormat.h"
#include "IOutputFormatFactory.h"

#include "MatrixOutputFormat.h"
#include "TableOutputFormat.h"
#include "ListOutputFormat.h"

using std::string;

const string IOutputFormatFactory::O_FORMAT_MATRIX = "MATRIX";
const string IOutputFormatFactory::O_FORMAT_TABLE = "TABLE";
const string IOutputFormatFactory::O_FORMAT_LIST = "LIST";

bool IOutputFormatFactory::isValidName(const string& name) {
	return 
		(name == O_FORMAT_MATRIX) ||
		(name == O_FORMAT_TABLE) ||
		(name == O_FORMAT_LIST);
}

const string* IOutputFormatFactory::getValidNames(size_t& numNames) {
	static size_t s_numNames = 3;
	static string s_names[] = {
		O_FORMAT_MATRIX,
		O_FORMAT_TABLE,
		O_FORMAT_LIST
	};

	numNames = s_numNames;
	return s_names;
}

IOutputFormat* IOutputFormatFactory::make(const string& name) {
	assert(isValidName(name));

	if(name == O_FORMAT_MATRIX) {
		return new MatrixOutputFormat();
	}

	if(name == O_FORMAT_TABLE) {
		return new TableOutputFormat();
	}

	if(name == O_FORMAT_LIST) {
		return new ListOutputFormat();
	}

	return NULL;
}
