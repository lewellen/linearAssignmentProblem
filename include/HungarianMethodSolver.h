#ifndef HUNGARIANMETHODSOLVER_H
#define HUNGARIANMETHODSOLVER_H

#include <list>
#include <utility>
#include <vector>

#include "Array2D.h"
#include "ISolver.h"

using std::list;
using std::pair;
using std::vector;

class HungarianMethodSolver : public ISolver {
public:
	HungarianMethodSolver();
	~HungarianMethodSolver();

	vector<size_t> operator() (const Array2D<double>& M) const; 

private:
	size_t findZeroCovering(
		const Array2D<double>& B, 
		list<size_t>& verticalLines, list<size_t>& horizontalLines) const;
};

#endif
