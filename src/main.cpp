#include <cassert>
#include <cstdlib>
#include <iostream>
#include <limits>

using std::cout;
using std::endl;
using std::numeric_limits;
using std::ostream;

template <typename T>
class Node {
public:
	T value;
	Node<T>* next;
	Node<T>* prev;	

	Node() {
		value = 0;
		next = NULL;
		prev = NULL;
	}
};

template<typename T>
class NodeIterator {
public:
	NodeIterator() {
		m_prev = NULL;
		m_cursor = NULL;
		m_next = NULL;
	}

	NodeIterator(Node<T>* cursor) {
		m_cursor = cursor;
		if(m_cursor == NULL) {
			m_prev = NULL;
			m_next = NULL;
		} else {
			m_prev = m_cursor->prev;
			m_next = m_cursor->next;
		}
	}

	NodeIterator(const NodeIterator<T>& other) {
		m_prev = other.m_prev;
		m_cursor = other.m_cursor;
		m_next = other.m_prev;
	}

	bool operator!= (const NodeIterator<T>& other) const {
		return m_cursor != other.m_cursor;
	}

	NodeIterator<T>& operator-- () {
		if(m_cursor != NULL) {
			m_next = m_cursor;
			m_cursor = m_prev;
			if(m_cursor == NULL) {
				m_prev = NULL;
			} else {
				m_prev = m_cursor->prev;
			}
		}

		return *this;
	}

	NodeIterator<T> operator-- (int) const {
		if(m_cursor == NULL) {
			return NodeIterator<T>(m_prev, m_cursor, m_next);
		}

		Node<T>* prev = NULL;
		if(m_prev != NULL) {
			prev = m_prev->prev;
		}

		return NodeIterator<T>(prev, m_prev, m_cursor);
	}

	NodeIterator<T>& operator++ () {
		if(m_cursor != NULL) {
			m_prev = m_cursor;
			m_cursor = m_next;
			if(m_cursor == NULL) {
				m_next = NULL;
			} else {
				m_next = m_cursor->next;
			}
		}

		return *this;
	}

	NodeIterator<T> operator++ (int) const {
		if(m_cursor == NULL) {
			return NodeIterator<T>();
		}

		Node<T>* next = NULL;
		if(m_next != NULL) {
			next = m_next->next;
		}

		return NodeIterator<T>(m_cursor, m_next, next);
	}

	T& operator* () const {
		assert(m_cursor != NULL);

		return m_cursor->value;
	}

	
private:
	Node<T>* m_prev;
	Node<T>* m_cursor;
	Node<T>* m_next;

	NodeIterator(Node<T>* prev, Node<T>* curr, Node<T>* next) {
		m_prev = prev;
		m_cursor = curr;
		m_next = next;
	}
};

template <typename T>
class ArrayView {
public:
	typedef NodeIterator<T> iterator;

	ArrayView(size_t entries) {
		assert(entries > 0);

		m_arraySize = entries;

		m_array = new Node<T>*[entries];
		for(size_t i = 0; i < m_arraySize; ++i) {
			m_array[i] = new Node<T>();
		}

		for(size_t i = 0; i < m_arraySize; ++i) {
			if(i > 0) {
				m_array[i]->prev = m_array[i-1];
			}

			if(i + 1 < m_arraySize) {
				m_array[i]->next = m_array[i+1];
			}
		}

		m_head = m_array[0];
	}

	~ArrayView() {
		for(size_t i = 0; i < m_arraySize; ++i) {
			delete m_array[i];
			m_array[i] = NULL;
		}

		delete[] m_array;
		m_array = NULL;

		m_arraySize = 0;
		m_head = NULL;
	}

	T& operator [](size_t index) {
		assert(index < m_arraySize);
		Node<T>* node = m_array[index];
		assert(node != NULL);
		return node->value;
	}

	const T& operator[] (size_t index) const {
		assert(index < m_arraySize);
		Node<T>* node = m_array[index];
		assert(node != NULL);
		return node->value;
	}

	iterator begin() {
		return iterator(m_head);
	}

	iterator end() {
		return iterator();
	}

	void erase(size_t index) {
		assert(index < m_arraySize);

		Node<T>* node = m_array[index];
		if(node == NULL) {
			return;
		}

		Node<T>* prev = node->prev;
		Node<T>* next = node->next;

		if(prev != NULL) {
			prev->next = next;
		}

		if(next != NULL) {
			next->prev = prev;
		}

		if(m_head == node) {
			m_head = next;
		}

		delete node;
		m_array[index] = NULL;
	}

private:
	size_t m_arraySize;
	Node<T>** m_array;
	Node<T>* m_head;
};


class CostMatrix {
public:
	typedef ArrayView<size_t>::iterator iterator;
	
	CostMatrix(size_t numEntries) {
		assert(numEntries > 0);
		m_numEntries = numEntries;
		
		m_rows = indexedView(m_numEntries);
		m_cols = indexedView(m_numEntries);

		m_matrix = new double[m_numEntries * m_numEntries];
		for(size_t row = 0; row < m_numEntries; ++row) {
			for(size_t col = 0; col < m_numEntries; ++col) {
				m_matrix[row * m_numEntries + col] = 0;
			}
		}
	}

	~CostMatrix() {
		m_numEntries = 0;

		delete m_rows;
		m_rows = NULL;

		delete m_cols;
		m_cols = NULL;

		delete[] m_matrix;
		m_matrix = NULL;
	}

	iterator rowBegin() {
		return m_rows->begin();
	}

	iterator rowEnd() {
		return m_rows->end();
	}

	iterator colBegin() {
		return m_cols->begin();
	}

	iterator colEnd() {
		return m_cols->end();
	}

	double& getEntry(size_t row, size_t col) {
		assert(row < m_numEntries);
		assert(col < m_numEntries);

		return m_matrix[row * m_numEntries + col];
	}

	const double& getEntry(size_t row, size_t col) const {
		assert(row < m_numEntries);
		assert(col < m_numEntries);

		return m_matrix[row * m_numEntries + col];	
	}

	void eraseRow(size_t i) {
		m_rows->erase(i);
	}

	void eraseCol(size_t i) {
		m_cols->erase(i);
	}	

	double getRowMin(size_t row) {
		assert(row < m_numEntries);

		double minValue = +numeric_limits<double>::infinity();
		for(ArrayView<size_t>::iterator i = m_cols->begin(); i != m_cols->end(); ++i) {
			double value = m_matrix[row * m_numEntries + *i];
			if(value < minValue) {
				minValue = value;
			}	
		}

		return minValue;
	}

	double getColMin(size_t col) {
		assert(col < m_numEntries);

		double minValue = +numeric_limits<double>::infinity();
		for(ArrayView<size_t>::iterator i = m_rows->begin(); i != m_rows->end(); ++i) {
			double value = m_matrix[(*i) * m_numEntries + col];
			if(value < minValue) {
				minValue = value;
			}
		}

		return minValue;
	}

	friend ostream& operator<< (ostream& s, CostMatrix& M) {
		for(CostMatrix::iterator row = M.rowBegin(); row != M.rowEnd(); ++row) {
			for(CostMatrix::iterator col = M.colBegin(); col != M.colEnd(); ++col) {
				s << M.getEntry(*row, *col) << " ";
			}
			s << endl;
		}
		return s;
	}

private:
	size_t m_numEntries;

	ArrayView<size_t>* m_rows;
	ArrayView<size_t>* m_cols;
	double* m_matrix;

	ArrayView<size_t>* indexedView(size_t numEntries) {
		ArrayView<size_t>* view = new ArrayView<size_t>(numEntries);
		assert(view != NULL);

		size_t index = 0;
		for(ArrayView<size_t>::iterator i = view->begin(); i != view->end(); ++i) {
			*i = index;
			++index;
		}

		return view;
	}
};

int main(int argc, char** argv) {

	CostMatrix M(5);

	// Initialize random cost matrix
	for(CostMatrix::iterator row = M.rowBegin(); row != M.rowEnd(); ++row) {
		for(CostMatrix::iterator col = M.colBegin(); col != M.colEnd(); ++col) {
			M.getEntry(*row, *col) = (rand() % 100) + 5;
		}
	}

	cout << M << endl;

	// Deduct row min from each row
	for(CostMatrix::iterator row = M.rowBegin(); row != M.rowEnd(); ++row) {
		double rowMin = M.getRowMin(*row);
		for(CostMatrix::iterator col = M.colBegin(); col != M.colEnd(); ++col) {
			M.getEntry(*row, *col) -= rowMin;
		}
	}

	cout << M << endl;

	// Deduct col min from each column
	for(CostMatrix::iterator col = M.colBegin(); col != M.colEnd(); ++col) {
		double colMin = M.getColMin(*col);
		for(CostMatrix::iterator row = M.rowBegin(); row != M.rowEnd(); ++row) {
			M.getEntry(*row, *col) -= colMin;
		}
	}

	cout << M << endl;

	// Draw minimum number of lines through all zeros

	// If there are N lines; done.

	// Find the smallest entry not covered by any line. Subtract value from each row 
	// that is not crossed out; then add it to each column that *IS* crossed out.
	// go back to (draw min num lines through all zeros step.)

	
	return EXIT_SUCCESS;
}
