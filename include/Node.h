#ifndef NODE_H
#define NODE_H

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

#endif
