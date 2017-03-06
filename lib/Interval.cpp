#include <cassert>
#include "Interval.h"

Interval::Interval() {
	initialize(0, 0);
}

Interval::Interval(const double& lb, const double& ub) {
	initialize(lb, ub);
}

Interval::Interval(const Interval& other) {
	initialize(other.m_lb, other.m_ub);
}

Interval::~Interval() {

}

const double& Interval::getLowerBound() const {
	return m_lb;
}

const double& Interval::getUpperBound() const {
	return m_ub;
}

void Interval::initialize(const double& lb, const double& ub) {
	assert(lb <= ub);
	m_lb = lb;
	m_ub = ub;
}

