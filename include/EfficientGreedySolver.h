#ifndef EFFICIENTGREEDYSOLVER_H
#define EFFICIENTGREEDYSOLVER_H

#include "Array2D.h"
#include "Assignment.h"
#include "GreedySolver.h"

class EfficientGreedySolver : public GreedySolver {
public:
	EfficientGreedySolver();
	~EfficientGreedySolver();

	Assignment operator() (const Array2D<double>& M) const;
};

#endif

