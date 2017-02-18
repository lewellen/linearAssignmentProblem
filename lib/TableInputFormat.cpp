#include <iostream>

#include "Array2D.h"
#include "TableInputFormat.h"

using std::istream;

TableInputFormat::TableInputFormat() {

}

TableInputFormat::~TableInputFormat() {

}

bool TableInputFormat::read(istream& s, Array2D<double>& M) const {
	return false;
}
