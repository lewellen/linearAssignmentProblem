#ifndef ARRAYMASK_H
#define ARRAYMASK_H

#include <cassert>

#include "Node.h"
#include "NodeIterator.h"

template <typename T>
class ArrayMask {
public:
	typedef NodeIterator<T> iterator;

	ArrayMask(size_t entries) {
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

	~ArrayMask() {
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

#endif
