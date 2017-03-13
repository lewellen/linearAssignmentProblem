#include <cmath>
#include <cstdlib>

#include "Array2D.h"
#include "RandomMatrix.h"

RandomMatrix::RandomMatrix(size_t rows, size_t cols) : Array2D<double>(rows, cols) {
	size_t N = 10 * (getNumRows() * getNumCols());

	for(size_t row = 0; row < getNumRows(); ++row) {
		for(size_t col = 0; col < getNumCols(); ++col) {
			getEntry(row, col) = (rand() % N) + 1;
			//getEntry(row, col) = rand() / RAND_MAX;
		}
	}
}
