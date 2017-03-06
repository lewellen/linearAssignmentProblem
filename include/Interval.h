#ifndef INTERVAL_H
#define INTERVAL_H

#include <iostream>

using std::ostream;

class Interval {
public:
	Interval();
	Interval(const double& lb, const double& ub); 
	Interval(const Interval& other);
	~Interval();
 
	const double& getLowerBound() const;
	const double& getUpperBound() const;

	friend ostream& operator<< (ostream& s, const Interval& I) {
		return s << "[" << I.m_lb << ", " << I.m_ub << "]";
	}
 
private:
	double m_lb, m_ub;

	void initialize(const double& lb, const double& ub);
};

#endif
