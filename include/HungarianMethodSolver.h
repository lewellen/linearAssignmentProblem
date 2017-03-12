#ifndef HUNGARIANMETHODSOLVER_H
#define HUNGARIANMETHODSOLVER_H

#include <list>

#include "Array2D.h"
#include "Assignment.h"
#include "IHungarianLog.h" 
#include "ISolver.h"

using std::list;

class HungarianMethodSolver : public ISolver {
public:
	HungarianMethodSolver();
	~HungarianMethodSolver();

	Assignment operator() (const Array2D<double>& M) const; 

	void setLog(IHungarianLog* log);

private:
	IHungarianLog* m_log;
};

#endif
