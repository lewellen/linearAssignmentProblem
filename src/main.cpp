#include <cassert>
#include <cstdlib>
#include <iostream>
#include <limits>

using std::cout;
using std::endl;
using std::numeric_limits;
using std::ostream;

typedef struct Node {
	size_t value;
	Node* next;
	Node* prev;	

	Node() {
		value = 0;
		next = NULL;
		prev = NULL;
	}
} Node;

template <size_t entries>
class CostMatrix {
public:
	class iterator {
	public:
		iterator(Node* head) {
			this->head = head;
		}

		iterator(const iterator& other) {
			this->head = other.head;
		}

		iterator& operator++ () {
			if(head != NULL) {
				head = head->next;	
			}
			return *this;
		}

		bool operator== (const iterator& other) const {
			return head == other.head;
		}

		bool operator!= (const iterator& other) const {
			return head != other.head;
		}

		size_t operator* () {
			assert(head != NULL);
			return head->value;
		}
	private:
		Node* head;
	};

	CostMatrix() {
		assert(entries > 0);

		for(size_t i = 0; i < entries; ++i) {
			rows[i] = new Node();
			rows[i]->value = i;

			cols[i] = new Node();
			cols[i]->value = i;
		}

		for(size_t i = 0; i < entries; ++i) {
			if(i > 0) {
				rows[i]->prev = rows[i-1];
				cols[i]->prev = cols[i-1];
			}
			if(i + 1 != entries) {
				rows[i]->next = rows[i+1];
				cols[i]->next = cols[i+1];
			}
		}

		rowHead = rows[0];
		colHead = cols[0];

		for(size_t row = 0; row < entries; ++row) {
			for(size_t col = 0; col < entries; ++col) {
				matrix[row * entries + col] = 0;
			}
		}
	}

	~CostMatrix() {
		for(size_t i = 0; i != entries; ++i) {
			if(rows[i] != NULL) {
				delete rows[i];
				rows[i] = NULL;
			}

			if(cols[i] != NULL) {
				delete cols[i];
				cols[i] = NULL;
			}
		}

		rowHead = colHead = NULL;
	}

	iterator rowBegin() {
		return iterator(rowHead);
	}

	iterator rowEnd() {
		return iterator(NULL);
	}

	iterator colBegin() {
		return iterator(colHead);
	}

	iterator colEnd() {
		return iterator(NULL);
	}

	double& getEntry(size_t row, size_t col) {
		assert(row < entries);
		assert(col < entries);

		return matrix[row * entries + col];
	}

	const double& getEntry(size_t row, size_t col) const {
		assert(row < entries);
		assert(col < entries);

		return matrix[row * entries + col];	
	}

	void eraseRow(size_t i) {
		assert(i < entries);

		if(rows[i] == NULL) {
			return;
		}

		Node* next = rows[i]->next;
		Node* prev = rows[i]->prev;

		if(next != NULL) {
			next->prev = prev; 
		}

		if(prev != NULL) {
			prev->next = next;
		}

		if(rowHead == rows[i]) {
			rowHead = next;
		}

		delete rows[i];
		rows[i] = NULL;
	}

	void eraseCol(size_t i) {
		assert(i < entries);

		if(cols[i] == NULL) {
			return;
		}

		Node* next = cols[i]->next;
		Node* prev = cols[i]->prev;

		if(next != NULL) {
			next->prev = prev; 
		}

		if(prev != NULL) {
			prev->next = next;
		}

		if(colHead == cols[i]) {
			colHead = next;
		}

		delete cols[i];
		cols[i] = NULL;
	}	

	double getRowMin(size_t row) {
		assert(row < entries);

		double minValue = +numeric_limits<double>::infinity();

		Node* cursor = colHead;
		while(cursor != NULL) {
			size_t col = cursor->value;
			double value = matrix[row * entries + col];
			if(value < minValue) {
				minValue = value;
			}

			cursor = cursor->next;
		}

		return minValue;
	}

	double getColMin(size_t col) {
		assert(col < entries);

		double minValue = +numeric_limits<double>::infinity();

		Node* cursor = rowHead;
		while(cursor != NULL) {
			size_t row = cursor->value;
			double value = matrix[row * entries + col];
			if(value < minValue) {
				minValue = value;
			}

			cursor = cursor->next;
		}

		return minValue;
	}

	friend ostream& operator<< (ostream& s, CostMatrix<entries>& M) {
		for(CostMatrix<entries>::iterator row = M.rowBegin(); row != M.rowEnd(); ++row) {
			for(CostMatrix<entries>::iterator col = M.colBegin(); col != M.colEnd(); ++col) {
				s << M.getEntry(*row, *col) << " ";
			}
			s << endl;
		}
		return s;
	}

private:
	Node* rowHead;
	Node* colHead;
	
	Node* rows[entries];
	Node* cols[entries];

	double matrix[entries * entries];
};



int main(int argc, char** argv) {
	CostMatrix<5> M;

	// Initialize random cost matrix
	for(CostMatrix<5>::iterator row = M.rowBegin(); row != M.rowEnd(); ++row) {
		for(CostMatrix<5>::iterator col = M.colBegin(); col != M.colEnd(); ++col) {
			M.getEntry(*row, *col) = (rand() % 100) + 5;
		}
	}

	cout << M << endl;

	// Deduct row min from each row
	for(CostMatrix<5>::iterator row = M.rowBegin(); row != M.rowEnd(); ++row) {
		double rowMin = M.getRowMin(*row);
		for(CostMatrix<5>::iterator col = M.colBegin(); col != M.colEnd(); ++col) {
			M.getEntry(*row, *col) -= rowMin;
		}
	}

	cout << M << endl;

	// Deduct col min from each column
	for(CostMatrix<5>::iterator col = M.colBegin(); col != M.colEnd(); ++col) {
		double colMin = M.getColMin(*col);
		for(CostMatrix<5>::iterator row = M.rowBegin(); row != M.rowEnd(); ++row) {
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
