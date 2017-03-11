#include <cassert>
#include <string>

#include "IOutputFormat.h"
#include "IOutputFormatFactory.h"

#include "LatexOutputFormat.h"
#include "ListOutputFormat.h"
#include "MatrixOutputFormat.h"
#include "TableOutputFormat.h"

using std::string;

const string IOutputFormatFactory::O_FORMAT_LATEX = "LATEX";
const string IOutputFormatFactory::O_FORMAT_LIST = "LIST";
const string IOutputFormatFactory::O_FORMAT_MATRIX = "MATRIX";
const string IOutputFormatFactory::O_FORMAT_TABLE = "TABLE";

bool IOutputFormatFactory::isValidName(const string& name) {
	return 
		(name == O_FORMAT_LATEX) ||
		(name == O_FORMAT_LIST) ||
		(name == O_FORMAT_MATRIX) ||
		(name == O_FORMAT_TABLE);
}

const string* IOutputFormatFactory::getValidNames(size_t& numNames) {
	static size_t s_numNames = 4;
	static string s_names[] = {
		O_FORMAT_LATEX,
		O_FORMAT_LIST,
		O_FORMAT_MATRIX,
		O_FORMAT_TABLE
	};

	numNames = s_numNames;
	return s_names;
}

IOutputFormat* IOutputFormatFactory::make(const string& name) {
	assert(isValidName(name));

	if(name == O_FORMAT_LATEX) {
		return new LatexOutputFormat();
	}

	if(name == O_FORMAT_LIST) {
		return new ListOutputFormat();
	}

	if(name == O_FORMAT_MATRIX) {
		return new MatrixOutputFormat();
	}

	if(name == O_FORMAT_TABLE) {
		return new TableOutputFormat();
	}

	return NULL;
}
