#include <iostream>
#pragma once

using namespace std;

template < typename T >
class list {
private:
	struct Node {
		Node() : anext(NULL) { }
		Node(const T& t) : at(t), anext(NULL) { }
		T at;
		Node* anext;
	};
	Node* ahead;
public:
	class Iterator {
	public:
		Iterator(Node* node) : anode(node) { }
		bool operator==(const Iterator& other) const {
			if (this == &other) {
				return true;
			}
			return anode == other.anode;
		}
		bool operator!=(const Iterator& other) const {
			return !operator==(other);
		}
		T operator*() const {
			if (anode) {
				return anode->m_t;
			}
			return T();
		}
		void operator++(int) {
			if (anode) {
				anode = anode->anext;
			}
		}
	private:
		Node* anode;
	};
public:
	list();
	~list();
	void append_beg(const T& t);
	void remove_beg();
	void append(Node* prev,const T& t);
	void append_end(const T& t);
	void remove(Node* prev);
	void remove_end();
	Iterator begin() const;
	Iterator end() const;
	size_t size() const;

};

template < typename T >
list< T >::list() : ahead(NULL) {
}

template < typename T >
void list < T >::append_beg(const T &t) {
	Node* node = new Node(t);
	node->anext = ahead;
	ahead = node;
}

template < typename T >
void list < T >::append(Node* prev,const T& t) {
	Node* a = new Node();
	a->at = t;
	a->anext = prev->anext;
	prev->anext = a;
}

template < typename T >
void list < T >::append_end(const T& t) {
	if (ahead == NULL) {
		append_beg(t);
		return;
	}
	Node* a = ahead;
	while (a->anext != NULL)
		a = a->anext;
	a->anext = new Node();
	a->anext->at = t;
	a->anext->anext = NULL;
}

template < typename T >
void list < T >::remove_beg() {
	if (ahead) {
		Node* newHead = ahead->anext;
		delete ahead;
		ahead = newHead;
	}
}

template < typename T >
void list < T >::remove(Node* prev) {
	if (prev->anext == NULL)
		throw 1;
	Node* a = prev->anext->anext;
	delete prev->anext;
	prev->anext = a;
}

template < typename T >
void list < T >::remove_end() {
	if (ahead == NULL)
		throw 1;
	if (ahead->anext == NULL) {
		remove_beg();
		return;
	}
	Node* a = ahead;
	while (ahead->anext->anext != NULL)
		ahead = ahead->anext;
	delete ahead->next;
	ahead->next = NULL;
	ahead = a;
}

template < typename T >
list < T >::~list() {
	while (ahead) {
		remove();
	}
}

template < typename T >
typename list < T >::Iterator list < T >::begin() const {
	return Iterator(ahead);
}

template < typename T >
typename list < T >::Iterator list < T >::end() const {
	return Iterator(NULL);
}

template< typename T >
size_t list < T >::size() const {
	size_t s = 0;
	for (Iterator it = begin(); it != end(); ++it) {
		++s;
	}
}
