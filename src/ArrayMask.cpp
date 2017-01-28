#include <cassert>
#include <cstdlib>

#include "Node.h"
#include "ArrayMask.h"

ArrayMask::ArrayMask(size_t entries) {
	assert(entries > 0);

	m_arraySize = entries;

	m_array = new Node<size_t>*[entries];
	for(size_t i = 0; i < m_arraySize; ++i) {
		m_array[i] = new Node<size_t>();
		m_array[i]->value = i;
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

ArrayMask::~ArrayMask() {
	for(size_t i = 0; i < m_arraySize; ++i) {
		delete m_array[i];
		m_array[i] = NULL;
	}

	delete[] m_array;
	m_array = NULL;

	m_arraySize = 0;
	m_head = NULL;
}

ArrayMask::iterator ArrayMask::begin() {
	return iterator(m_head);
}

ArrayMask::iterator ArrayMask::end() {
	return iterator();
}

void ArrayMask::erase(size_t index) {
	assert(index < m_arraySize);

	Node<size_t>* node = m_array[index];
	if(node == NULL) {
		return;
	}

	Node<size_t>* prev = node->prev;
	Node<size_t>* next = node->next;

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

