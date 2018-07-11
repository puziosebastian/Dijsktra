#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template<class T>

struct Node {

	Node() : next(nullptr), prev(nullptr) {}

	T value;
	Node<T> * next;
	Node<T> * prev;
};

template<class T>

class LinkedList {

public:

	LinkedList() : m_size(0), m_head(new Node<T>()), m_cursor(nullptr) {}

	void insert_first(T value) {
		Node<T> * newNode = new Node<T>();
		newNode->value = value;
		newNode->next = m_head->next;
		m_head->next = m_cursor = newNode;
		newNode->prev = m_head;
		++m_size;
	}

	~LinkedList() {
		Node<T> * next, *cur = m_head->next;
		while (cur) {
			next = cur->next;
			delete cur;
			cur = next;
		}
	}

	int size() {
		return m_size;
	}

	void reset_cursor() {
		m_cursor = m_head->next;
	}

	T * previous() {

		if (!m_cursor)

			return nullptr;

		T * ret = &(m_cursor->value);
		m_cursor = m_cursor->prev;
		return ret;
	}

	T * next() {

		if (!m_cursor)

			return nullptr;

		T * ret = &(m_cursor->value);
		m_cursor = m_cursor->next;
		return ret;
	}

private:
	int m_size;
	Node<T> * m_head;
	Node<T> * m_cursor;
};

#endif //LINKED_LIST_H


