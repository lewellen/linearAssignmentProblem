#ifndef ARRAYMASK_H
#define ARRAYMASK_H

#include <cassert>
#include <cstdlib>

#include "Node.h"
#include "NodeIterator.h"

class ArrayMask {
public:
	typedef NodeIterator<size_t> iterator;

	ArrayMask(size_t entries);
	~ArrayMask();

	iterator begin();
	iterator end();
	void erase(size_t index);

private:
	size_t m_arraySize;
	Node<size_t>** m_array;
	Node<size_t>* m_head;
};

#endif
