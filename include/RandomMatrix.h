#ifndef RANDOMMATRIX_H
#define RANDOMMATRIX_H

#include <cstdlib>

#include "Array2D.h"

class RandomMatrix : public Array2D<double> {
public:
	RandomMatrix(size_t rows, size_t cols); 
};

#endif
