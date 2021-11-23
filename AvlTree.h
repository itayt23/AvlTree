#ifndef AVLTREE
#define AVLTREE
#include <math.h>
#include "AvlNode.h"



template<class T> 
class AvlTree 
{	
	AvlNode<T>* root;

	public:

		/*
        * AvlTree: c'tor with no given parameters of AvlTree class.
        **/
		AvlTree();

		/*
        * ~AvlTree: d'tor of AvlTree class.
        **/
		~AvlTree();

		void insert(T* key);
		void remove(T* key);
		bool isEmpty();
		void inOrder(const AvlNode<T>* node);//is it const? 
		void postOrder(const AvlNode<T>* node);
		void preOrder(const AvlNode<T>* node);

		AvlNode<T>* search(T* key);
		
};

template<class T>
AvlTree<T>::AvlTree() : root(nullptr){} //root(AvlNode()) {}

template<class T>
AvlTree<T>::~AvlTree()
{
	if(this->root != nullptr)
	{
		root->clearAll();
		delete root;
		root = nullptr;
	}
}

template<class T>
bool AvlTree<T>::isEmpty()
{
	if(this->root == nullptr)
	{
		return true;
	}
	return false;
}

template<class T>
void AvlTree<T>::insert(T* add)
{
	if(this->root == nullptr) // the tree is empty
	{
		this->root = new AvlNode<T>(add,nullptr);
	}
	else
	{
		this->root = this->root->insert(add);
	}
}

template<class T>
AvlNode<T>* AvlTree<T>::search(T* key_find)
{
	if(this->root == nullptr) // if the tree is empty
	{
		return "exception"
	}
	return this->root->search(key_find);
}



#endif