#include <algorithm>
#include <cmath>
#include <cassert>
#include <limits>
#include <list>
#include <utility>
#include <queue>

#include "Array2D.h"
#include "Array2DMask.h"
#include "Assignment.h"
#include "ISolver.h"
#include "GreedySolver.h"

#include <iostream>
using std::cout;
using std::endl;

using std::list;
using std::numeric_limits;
using std::pair;
using std::queue;
using std::sort;

GreedySolver::GreedySolver() {

}

GreedySolver::~GreedySolver() {

}

Assignment GreedySolver::cubicImpl(const Array2D<double>& A) const {
	assert(A.getNumRows() == A.getNumCols());

	// As written this is O(n^3), but I believe with smarter data structs
	// should make this more efficient.

	Assignment assignment(A.getNumRows());
		
	Array2DMask M(A.getNumRows(), A.getNumCols());

	for(size_t i = 0; i < A.getNumRows(); ++i) {
		double min = numeric_limits<double>::infinity();
		size_t minRow = 0;
		size_t minCol = 0;

		for(Array2DMask::iterator row = M.begin(0); row != M.end(0); ++row) {
			for(Array2DMask::iterator col = M.begin(1); col != M.end(1); ++col) {
				const double& value = A.getEntry(*row, *col);
				if(min > value) {
					min = value;
					minRow = *row;
					minCol = *col;
				}
			}
		}

		assignment[ minRow ] = minCol;
		M.erase(0, minRow);
		M.erase(1, minCol);
	}

	return assignment;
}

struct QNode {
	double value;
	size_t row;
	size_t col;

	QNode* left;
	QNode* right;
	QNode* up;
	QNode* down;

	QNode* prev;
	QNode* next;

	QNode(const double& value, const size_t row, const size_t col) {
		this->value = value;
		this->row = row;
		this->col = col;

		left = right = up = down = NULL;
		prev = next = NULL;
	}
};

bool QNodeValueLess(const QNode* a, const QNode* b) {
	assert(a != NULL);
	assert(b != NULL);
	return a->value < b->value;
};

enum DeleteAction {
	DA_THIS,
	DA_LEFT,
	DA_RIGHT,
	DA_UP,
	DA_DOWN
};

struct DeleteTask {
	QNode* node;
	DeleteAction action;

	DeleteTask(QNode* node, DeleteAction action) {
		this->node = node;
		this->action = action;
	}
};

Assignment GreedySolver::quadarithmicImpl(const Array2D<double>& A) const {
	assert(A.getNumRows() == A.getNumCols());

	// This is a O( n^2 log n ) impl

	Assignment assignment(A.getNumRows());

	const size_t nodesSize = A.getNumRows() * A.getNumCols();
	QNode* nodes[nodesSize];

	for(size_t row = 0; row < A.getNumRows(); ++row) {
		for(size_t col = 0; col < A.getNumCols(); ++col) {
			size_t index = row * A.getNumRows() + col;
			nodes[index] = new QNode(A.getEntry(row, col), row, col);
		}
	}

	for(size_t row = 0; row < A.getNumRows(); ++row) {
		for(size_t col = 0; col < A.getNumCols(); ++col) {
			size_t index = row * A.getNumRows() + col;

			if(row > 0) {
				size_t upIndex = (row - 1) * A.getNumRows() + col;
				nodes[index]->up = nodes[upIndex];
			}

			if(row + 1 < A.getNumRows()) {
				size_t downIndex = (row + 1) * A.getNumRows() + col;
				nodes[index]->down = nodes[downIndex];
			}

			if(col > 0) {
				size_t leftIndex = row * A.getNumRows() + (col - 1);
				nodes[index]->left = nodes[leftIndex];
			}

			if(col + 1 < A.getNumCols()) {
				size_t rightIndex = row * A.getNumRows() + (col + 1);
				nodes[index]->right = nodes[rightIndex];
			} 
		}
	}

	std::sort( nodes, nodes + nodesSize, &QNodeValueLess );

	for(size_t i = 0; i < nodesSize; ++i) {
		QNode* node = nodes[i];
		if(i > 0) {
			node->prev = nodes[i - 1];
			assert(node->prev->value <= node->value);
		}

		if(i + 1 < nodesSize) {
			node->next = nodes[i + 1];
			assert(node->next->value >= node->value);
		}
	}


	QNode* cursor = nodes[0];
	while(cursor != NULL) {
		assignment[ cursor->row ] = cursor->col;

		QNode* nextCursor = cursor->next;

		// Delete row and col; but also maintain all the links.
		queue< DeleteTask > Q;
		Q.push( DeleteTask( cursor, DA_THIS ) );

		while(!Q.empty()) {
			DeleteTask& dt = Q.front();
			QNode* q = dt.node;
			DeleteAction da = dt.action;
			Q.pop();

			if(q->left != NULL) {
				if(da == DA_THIS || da == DA_LEFT) {
					Q.push( DeleteTask( q->left, DA_LEFT ) );
				}
				q->left->right = NULL;
			}

			if(q->right != NULL) {
				if(da == DA_THIS || da == DA_RIGHT) {
					Q.push( DeleteTask( q->right, DA_RIGHT ) );
				}
				q->right->left = NULL;
			}

			if(q->up != NULL) {
				if(da == DA_THIS || da == DA_UP) {
					Q.push( DeleteTask( q->up, DA_UP ) );
				}
				q->up->down = NULL;
			}

			if(q->down != NULL) {
				if(da == DA_THIS || da == DA_DOWN) {
					Q.push( DeleteTask( q->down, DA_DOWN ) );
				}
				q->down->up = NULL;
			}

			if(nextCursor == q) {
				nextCursor = q->next;
			}

			if(q->prev != NULL) {
				q->prev->next = q->next;
			}

			if(q->next != NULL) {
				q->next->prev = q->prev;
			}

			size_t index = q->row * A.getNumRows() + q->col;
			nodes[index] = NULL;
			delete q;
		}

		cursor = nextCursor;
	}

	return assignment;
}


Assignment GreedySolver::operator() (const Array2D<double>& A) const {
	return quadarithmicImpl(A);
}

