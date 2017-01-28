#ifndef ARRAY_H
#define ARRAY_H

#include <cassert>

template <typename T>
class Array {
public:
	Array(size_t size) {
		assert(size > 0);
		m_size = size;
		m_array = new T[size];
		assert(m_array != NULL);
	}

	Array(const Array& other) {
		m_size = other.m_size;
		m_array = new T[m_size];
		for(size_t i = 0; i < m_size; ++i) {
			m_array[i] = other[i];
		}
	}

	~Array() {
		delete[] m_array;
		m_array = NULL;
		m_size = 0;
	}
	
	T& operator[] (size_t index) {
		assert(index < m_size);
		return m_array[index];
	}

	const T& operator[] (size_t index) const {
		assert(index < m_size);
		return m_array[index];
	}
	
	const size_t& getSize() const {
		return m_size;
	}

private:
	size_t m_size;
	T* m_array;
};

#endif
