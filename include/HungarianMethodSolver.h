#ifndef HUNGARIANMETHODSOLVER_H
#define HUNGARIANMETHODSOLVER_H

#include <list>

#include "Array2D.h"
#include "Assignment.h"
#include "ISolver.h"

using std::list;

class HungarianMethodSolver : public ISolver {
public:
	HungarianMethodSolver();
	~HungarianMethodSolver();

	Assignment operator() (const Array2D<double>& M) const; 

private:
	size_t findZeroCovering(
		const Array2D<double>& B, 
		list<size_t>& verticalLines, list<size_t>& horizontalLines) const;
};

#endif
