#ifndef _RBT_H
#define _RBT_H 

#include <iostream>
#include <list>
#include "color.h"
#include "rbt_node.h"
#include "display_info.h"

template <typename T>
class RBT {

	private:
		RBT_Node<T> * root;
		RBT_Node<T> * nil_node;

		bool transplant(RBT_Node<T> *u, RBT_Node<T> *v);
		void inorder(RBT_Node<T> *location, std::ostream& out) const;
		void preorder(RBT_Node<T> *location, std::ostream& out) const;
		void postorder(RBT_Node<T> *location, std::ostream& out) const;
		RBT_Node<T>& search(RBT_Node<T> *f, long key) const;
		void free(RBT_Node<T> *root);
		RBT_Node<T>& max(RBT_Node<T> *root) const; 
		RBT_Node<T>& min(RBT_Node<T> *root) const; 
		void left_rotate(RBT_Node<T> *z);
		void right_rotate(RBT_Node<T> *z);
		void insert_fixup(RBT_Node<T> *z);

	public:
		RBT() {
			root = NULL;
			nil_node = new RBT_Node<T>;
			root = nil_node;
			nil_node->color = Black;
			nil_node->key = 0;
		}

		~RBT() {
			free(root);
			delete nil_node;
		}

		bool insert(long key, T data);
		bool remove(long key);
		RBT_Node<T>& search(long key) const;
		RBT_Node<T>&  max() const;
		RBT_Node<T>&  min() const;
		void inorder(std::ostream& out) const;
		void preorder(std::ostream& out) const;
		void postorder(std::ostream& out) const;
		void display() const;
};

template <typename T>
bool RBT<T>::transplant(RBT_Node<T> *u, RBT_Node<T> *v) {
	if(!u->p) {
		root = v;
	} else if(u == u->p->l) {
		u->p->l = v;
	} else if(u == u->p->r) {
		u->p->r = v;
	}
	if(v) {
		v->p = u->p;
	}

	return true;
}

template <typename T>
void RBT<T>::inorder(RBT_Node<T> *root, std::ostream& out) const {
	if(root != nil_node) {
		if(root->l != nil_node) {
			inorder(root->l, out);
		}
		out << (root->key) << "[" << (root->data) << "," << (root->color) << "]\t";
		if(root->r != nil_node) {
			inorder(root->r, out);
		}	
	} else {
		out << "Empty" << std::endl;
	}
}

template <typename T>
void RBT<T>::preorder(RBT_Node<T> *root, std::ostream& out) const {
	if(root != nil_node) {
		out << (root->key) << "[" << (root->data) << "," << (root->color) << "]\t";
		if(root->l != nil_node) {
			preorder(root->l, out);
		}
		if(root->r != nil_node) {
			preorder(root->r, out);
		}
	} else {
		out << "Empty" << std::endl;
	}
}

template <typename T>
void RBT<T>::postorder(RBT_Node<T> *root, std::ostream& out) const {
	if(root != nil_node) {
		if(root->l != nil_node) {
			postorder(root->l, out);
		}
		if(root->r != nil_node) {
			postorder(root->r, out);
		}
		out << (root->key) << "[" << (root->data) << "," << (root->color) << "]\t";
	} else {
		out << "Empty" << std::endl;
	}
}

template <typename T>
void RBT<T>::free(RBT_Node<T> *root) {
	if(root != nil_node) {
		if(root->l) {
			free(root->l);
		}
		if(root->r) {
			free(root->r);
		}	
		delete root;
		root = NULL;
	}
}

template <typename T>
void RBT<T>::inorder(std::ostream& out) const {
	inorder(root, out);
}

template <typename T>
void RBT<T>::preorder(std::ostream& out) const {
	preorder(root, out);
}

template <typename T>
void RBT<T>::postorder(std::ostream& out) const {
	postorder(root, out);
}

template <typename T>
bool RBT<T>::insert(long key, T data) { 
	RBT_Node<T> *p = root; 
	RBT_Node<T> *c = root;
	bool left = false;
	if(root) {
		while(c != NULL) {
			p = c;
			if(c->key == key) {
				c->data = data;
				return true;
			} else if(key > c->key) { 
				c = c->r;
				left = false;
			} else if(key < c->key) {
				c = c->l;
				left = true;
			}
		}

		if(left) {
			p->l = new RBT_Node<T>;
			c = p->l;
		} else {
			p->r = new RBT_Node<T>;
			c = p->r;
		}

	} else {
		root = new RBT_Node<T>;
		c = root;
	}
	c->p = p;
	c->data = data;
	c->color = Red;
	c->key = key;
	c->r = NULL;
	c->l = NULL;
	c->valid = true;

	return true;
}

template <typename T>
bool RBT<T>::remove(long key) { 
	if(root == nil_node) return false;
	RBT_Node<T> *z = &(search(key));
	RBT_Node<T> *y = NULL;
	if(!z->valid) return false;
	if(!z->l) {
		transplant(z,z->r);
	} else if(!z->r) {
		transplant(z,z->l);
	} else {
		y = &min(z->r);
		if(y->p != z) {
			transplant(y, y->r);
			y->r = z->r;
			y->r->p = y;
		}
		transplant(z, y);
		y->l = z->l;
		y->l->p = y;
	}
	delete z;
	return true;
}

template <typename T>
RBT_Node<T>& RBT<T>::search(RBT_Node<T> *f, long key) const{
	RBT_Node<T> *i = f;
	if(i->key == key) 
	  return *i;
	else if(i->r != nil_node && key > i->key)
	  return search(i->r, key);
	else if(i->l != nil_node && key < i->key)
	  return search(i->l, key);
	return *nil_node;
}

template <typename T>
RBT_Node<T>& RBT<T>::search(long key) const{
	return search(root, key);
}

template <typename T>
RBT_Node<T>& RBT<T>::max(RBT_Node<T> *root) const {
	RBT_Node<T> *i = root;
	if(root != nil_node) {
		while(i->r) i = i->r;
		return *i;
	} else {
		return *nil_node;
	}
}

template <typename T>
RBT_Node<T>& RBT<T>::min(RBT_Node<T> *root) const {
	RBT_Node<T> *i = root;
	if(root != nil_node) {
		while(i->l != nil_node) i = i->l;
		return *i;
	} else {
		return *nil_node; 
	}
}

template <typename T>
RBT_Node<T>& RBT<T>::max() const {
	return max(root);
}

template <typename T>
RBT_Node<T>& RBT<T>::min() const {
	return min(root);
}

template <typename T>
std::ostream& operator<<(std::ostream &out, const RBT<T> & rbt) {
	rbt.inorder(out);
	return out;
} 

template <typename T>
void RBT<T>::display() const {
	int i;
	std::list<RBT_Node<T> *> q;
	std::list<Display_Info> qi;
	int screen_width = 180;
	int data_width = 2;
	Display_Info info;    
	Display_Info preinfo; 
	RBT_Node<T> *curnode;       
	Display_Info curinfo; 
	if(root == nil_node) {
		std::cout << "Empty" << std::endl;
		return;
	}
	q.push_back(root);
	info.level = 1;
	info.enter = true;
	info.space_num = screen_width >> info.level;
	info.pos = info.space_num;
	qi.push_back(info);
	preinfo = info;
	while(q.size()) {
		curnode = q.front();
		q.pop_front();
		curinfo = qi.front();
		if(curinfo.enter) 
		  std::cout << "\n\n";
		for(i=0;i<curinfo.space_num;i++)
		  std::cout << " ";
		std::cout << curnode->key << ',' << curnode->color;
		qi.pop_front();
		if(curnode->l != nil_node) {
			q.push_back(curnode->l);
			info.level = curinfo.level + 1;
			info.pos = curinfo.pos - (screen_width >> info.level);
			if(info.level > preinfo.level) {
				info.enter = true;
				info.space_num = info.pos;
			} else {
				info.enter = false;
				info.space_num = info.pos - preinfo.pos;
			}
			info.space_num -= data_width;
			qi.push_back(info);
			preinfo = info;

		}
		if(curnode -> r != nil_node) {
			q.push_back(curnode -> r);
			info.level = curinfo.level + 1;
			info.pos = curinfo.pos + (screen_width >> info.level);
			if(info.level > preinfo.level) {
				info.enter = true;
				info.space_num = info.pos;
			} else {
				info.enter = false;
				info.space_num = info.pos - preinfo.pos;
			}
			info.space_num -= data_width;
			qi.push_back(info);
			preinfo = info;
		}

	}
	std::cout << std::endl;
}

#endif
