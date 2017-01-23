#ifndef NODEITERATOR_H
#define NODEITERATOR_H

#include <cassert>

#include "Node.h"

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

#endif
