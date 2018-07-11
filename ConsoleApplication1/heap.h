#ifndef HEAP_H
#define HEAP_H

#include "Graph.h"

class MinHeap {

public:
	MinHeap(int size)
		: m_size(0),
		m_capacity(size),
		m_weights(new int[size]),
		m_heap(new int[size]),
		m_heapIndices(new int[size])
	{
		
		for (int i = 0; i<m_capacity; ++i) {
			m_weights[i] = MAX_INT;
			m_heapIndices[i] = MAX_INT;
		}
	}

	MinHeap(int * weights, int * indices, int * heap_indices, int size)
		: m_size(size),
		m_weights(weights),
		m_heap(indices),
		m_heapIndices(heap_indices)
	{

	}

	~MinHeap() {
		delete[] m_weights;
		delete[] m_heap;
		delete[] m_heapIndices;
	}

	void reset() {
		for (int i = 0; i<m_capacity; ++i) {
			m_weights[i] = MAX_INT;
			m_heapIndices[i] = MAX_INT;
		}

		m_size = 0;
	}

	int get_min() {
		int ret = m_heap[0];
		m_heapIndices[m_heap[0]] = MAX_INT;
		m_heap[0] = m_heap[--m_size];
		
	    if (m_size) {
			m_heapIndices[m_heap[0]] = 0;
			sink_down(m_heap[0]);
		}

		return ret;
	}

	int * get_weights() {
		return m_weights;
	}

	bool empty() {
		return m_size == 0;
	}

	bool contains(int index) {
		return m_heapIndices[index] != MAX_INT;
	}

	void replace(int index, int weight) {
		if (m_heapIndices[index] == MAX_INT) insert(index, weight);

		else {
			m_weights[index] = weight;
			bubble_up(index);
			sink_down(index);
		}
	}

	void insert(int index, int weight) {
		m_weights[index] = weight;
		m_heap[m_size] = index;
		m_heapIndices[index] = m_size;
		++m_size;
		bubble_up(index);
	}

	void remove(int index) {
		if (m_heapIndices[index] == MAX_INT || m_size == 0) return;

		--m_size;
		swap(m_heapIndices[index], m_heapIndices[m_heap[m_size]]);

		if (m_size)
			sink_down(index);

		m_heapIndices[index] = MAX_INT;
	}

	void bubble_up(int index) {
		index = m_heapIndices[index];
		int parentIndex;

		for (; index; index = parentIndex) {
			parentIndex = (index - 1) / 2;
			if (m_weights[m_heap[index]] >= m_weights[m_heap[parentIndex]]) break;

			swap(index, parentIndex);
		}
	}

	void print() {
		printf("weig: ");
		for (int i = 0; i<m_capacity; ++i) {
			printf("%d ", m_weights[i]);
		}

		printf("\n");
		printf("h   : ");

		for (int i = 0; i<m_capacity; ++i) {
			printf("%d ", m_heap[i]);
		}

		printf("\n");
		printf("hp  : ");

		for (int i = 0; i<m_capacity; ++i) {
			printf("%d ", m_heapIndices[i]);
		}

		printf("\n\n\n");
	}

private:

	void swap(int i1, int i2) {
		int tmp = m_heap[i1];
		m_heap[i1] = m_heap[i2];
		m_heap[i2] = tmp;

		tmp = m_heapIndices[m_heap[i1]];
		m_heapIndices[m_heap[i1]] = m_heapIndices[m_heap[i2]];
		m_heapIndices[m_heap[i2]] = tmp;
	}

	void sink_down(int index) {
		int left, right, min, orig = index;
		index = m_heapIndices[index];
		while (true) {
			left = 2 * index + 1;
			right = left + 1;

			if (left >= m_size) break;

			min = left;

			if (right < m_size && m_weights[m_heap[right]] < m_weights[m_heap[min]])
				min = right;

			if (m_weights[m_heap[index]] <= m_weights[m_heap[min]]) break;

			swap(index, min);
			index = min;
		}
	}

	int m_size, m_capacity;
	int * m_weights;
	int * m_heap;
	int * m_heapIndices;
};

#endif //HEAP_H


