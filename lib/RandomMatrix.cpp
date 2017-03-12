#include <cmath>
#include <cstdlib>

#include "Array2D.h"
#include "RandomMatrix.h"

RandomMatrix::RandomMatrix(size_t rows, size_t cols) : Array2D<double>(rows, cols) {
	for(size_t row = 0; row < getNumRows(); ++row) {
		for(size_t col = 0; col < getNumCols(); ++col) {
			getEntry(row, col) = (rand() % 100) + 10;
		}
	}
}
