#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <cassert>
#include <cstdlib>

template <typename T>
class Array2D {
public:
	Array2D(size_t squareEdgeSize) {
		initialize(squareEdgeSize, squareEdgeSize);
	}

	Array2D(size_t rows, size_t cols) {
		initialize(rows, cols);
	}

	Array2D(const Array2D<T>& other) {
		initialize(other.m_rows, other.m_cols);

		for(size_t i = 0; i < m_rows; ++i) {
			for(size_t j = 0; j < m_cols; ++j) {
				m_array[i * m_cols + j] = other.m_array[i * m_cols + j];
			}
		}
	}

	~Array2D() {
		m_rows = 0;
		m_cols = 0;
		delete[] m_array;
		m_array = NULL;
	}

	const size_t& getNumRows() const {
		return m_rows;
	}

	const size_t& getNumCols() const {
		return m_cols;
	}

	T& getEntry(size_t row, size_t col) {
		assert(row < m_rows);
		assert(col < m_cols);
		return m_array[row * m_cols + col];
	}

	const T& getEntry(size_t row, size_t col) const {
		assert(row < m_rows);
		assert(col < m_cols);
		return m_array[row * m_cols + col];
	}

private:
	size_t m_rows;
	size_t m_cols;

	T* m_array;

	void initialize(size_t rows, size_t cols) {
		assert(rows > 0);
		assert(cols > 0);

		m_rows = rows;
		m_cols = cols;

		m_array = new T[rows * cols];
		assert(m_array != NULL);
	}
};

#endif
