#ifndef _RBT_NODE_H
#define _RBT_NODE_H

#include "color.h"

template <typename T>
struct RBT_Node {
	long key;
	RBT_Node<T> *l;
	RBT_Node<T> *r;
	RBT_Node<T> *p;
	Color color;
	T data;
	bool valid;
};

#endif
