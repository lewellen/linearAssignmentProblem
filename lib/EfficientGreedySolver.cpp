#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <queue>

#include "Array2D.h"
#include "Assignment.h"
#include "EfficientGreedySolver.h"

using std::queue;
using std::sort;

EfficientGreedySolver::EfficientGreedySolver() {

}

EfficientGreedySolver::~EfficientGreedySolver() {

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

Assignment EfficientGreedySolver::operator() (const Array2D<double>& A) const {
	assert(A.getNumRows() == A.getNumCols());

	// This is a O( n^2 log n ) impl

	Assignment assignment(A.getNumRows());

	if(m_log != NULL) {
		m_log->input(A);
	}

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

	sort( nodes, nodes + nodesSize, &QNodeValueLess );

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
		if(m_log != NULL) {
			m_log->afterAssignment(A, assignment, cursor->row, cursor->col);
		}

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
				q->left->right = q->right;
			}

			if(q->right != NULL) {
				if(da == DA_THIS || da == DA_RIGHT) {
					Q.push( DeleteTask( q->right, DA_RIGHT ) );
				}
				q->right->left = q->left;
			}

			if(q->up != NULL) {
				if(da == DA_THIS || da == DA_UP) {
					Q.push( DeleteTask( q->up, DA_UP ) );
				}
				q->up->down = q->down;
			}

			if(q->down != NULL) {
				if(da == DA_THIS || da == DA_DOWN) {
					Q.push( DeleteTask( q->down, DA_DOWN ) );
				}
				q->down->up = q->up;
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

	if(m_log != NULL) {
		m_log->output(A, assignment);
	}

	return assignment;
}

