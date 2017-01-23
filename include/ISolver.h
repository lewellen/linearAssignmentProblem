#ifndef ISOLVER_H
#define ISOLVER_H

#include <list>
#include <utility>

#include "CostMatrix.h"

using std::list;
using std::pair;

class ISolver {
public:
	ISolver();
	virtual ~ISolver();

	virtual list< pair<size_t, size_t> > operator() (CostMatrix& M) = 0;
};

#endif
