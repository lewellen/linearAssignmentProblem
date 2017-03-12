#ifndef GREEDYSOLVER_H
#define GREEDYSOLVER_H

#include "Array2D.h"
#include "Assignment.h"
#include "IGreedyLog.h"
#include "ISolver.h"

class GreedySolver : public ISolver {
public:
	GreedySolver();
	virtual ~GreedySolver();

	virtual Assignment operator() (const Array2D<double>& M) const = 0;

	void setLog(IGreedyLog* log);

protected:
	IGreedyLog* m_log;
};

#endif

