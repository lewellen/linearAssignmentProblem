#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <cstdlib>
#include <iostream>
#include <vector>

#include "Array2D.h"

using std::ostream;
using std::vector;

class Assignment {
public:
	Assignment(size_t numWorkers);
	Assignment(const Assignment& other);

	Assignment& operator= (const Assignment& other);	

	~Assignment();

	double cost(const Array2D<double>& M) const;
	ostream& display(ostream& s, const Array2D<double>& M) const;

	size_t size() const;
	size_t& operator[] (size_t index);
	const size_t& operator[] (size_t index) const;

	friend ostream& operator<< (ostream& s, const Assignment& a);

private:
	size_t m_size;
	vector<size_t> m_v;
};

#endif
