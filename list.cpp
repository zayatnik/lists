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
		void operator++() {
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
	void append(const T& t);
	void remove();
	Iterator begin() const;
	Iterator end() const;
	size_t size() const;

};

template < typename T >
list< T >::list() : ahead(NULL) {
}

template < typename T >
void list < T >::append(const T &t) {
	Node* node = new Node(t);
	node->anext = ahead;
	ahead = node;
}

template < typename T >
void list < T >::remove() {
	if (ahead) {
		Node* newHead = ahead->anext;
		delete ahead;
		ahead = newHead;
	}
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
