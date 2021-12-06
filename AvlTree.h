#ifndef AVLTREE
#define AVLTREE

#include <cmath>
#include "AvlNode.h"
#include "exceptions.h"


template<class T> 
class AvlTree {	
	AvlNode<T>* root;
	int 		size;
	public:
		AvlTree();
		AvlTree(AvlNode<T>* root, int size);
		~AvlTree();
		void insert(T key);			//! memory allocation
		void remove(T key);			//! memory allocation
		AvlNode<T>* search(T key);	//! memory allocation
		AvlNode<T>* getRootNode();
		AvlNode<T>* getMaxNode();
		void setRootNode(AvlNode<T>* new_root);
		bool isEmpty();
		void inOrder();	 
		void inOrderReverse();
		void clearTree();
		int getSize() const;
		class Empty {};
		class NodeAlreadyExists {};
		class DoesntExist {};
};

template<class T>
AvlTree<T>::AvlTree() : root(nullptr), size(0){}
template<class T>
AvlTree<T>::AvlTree(AvlNode<T>* root, int size) : root(root), size(size){}

template<class T>
AvlTree<T>::~AvlTree()
{
	if(this->root != nullptr){
		root->clearAll();
		delete root;
		root = nullptr;
	}
}

template<class T>
bool AvlTree<T>::isEmpty(){
	return (size == 0);
}

template<class T>
AvlNode<T>* AvlTree<T>::getRootNode(){
	return this->root;
}

/**
 * @brief recieves a data and stores it inside a node in the tree.
 * @tparam the type of the oobject being insert must have operators: ==, <, >
 * @throw NodeExist - if there's a node with the same key
 * 			std::bad_alloc& exception - out of memory
 * @param add - the object we wish to store. 
 */
template<class T>
void AvlTree<T>::insert(T add){
	/*
	if(add == nullptr){
		return;
	}*/
	T* temp_add;
	try {
		temp_add = new T(add);
	} catch (std::bad_alloc& e) {
		throw e;
		}
	if(temp_add == nullptr) return;
	if(this->root == nullptr){	// if the tree is empty// if(this->root == nullptr){
		try {
			this->root = new AvlNode<T>(temp_add,nullptr);
		} catch (std::bad_alloc& e) {	// this block is not futile.
			delete temp_add;
			throw e; // throw std::bad_alloc	//TODO: Catch.
		}
	}
	else if(this->root->search(temp_add) != nullptr){ // there is already the same value inside.
		delete temp_add;
		throw NodeAlreadyExist();		//TODO: Catch.
	} else {
		try{
			this->root = this->root->insert(temp_add);	// AvlNode.insert may throw bad_alloc.
		} catch (std::bad_alloc& e){
			delete temp_add; 
			throw e;	// throw std::bad_alloc	//TODO: Catch.
		}
	}
	size++;	// in case of success. 
}

/**
 * @brief searches for a given key in the tree
 * @throw Empty if the tree is empty
 * 		std::bad_alloc& - out of memory
		NodeDosentExist - if there no node with the given key. 
 * @param key - the searches key.
 * @return AvlNode<T>* - returns a pointer to the node containing the the key. 
 */
template<class T>
AvlNode<T>* AvlTree<T>::search(T key){
	T* temp_key_find;
	try {
		temp_key_find = new T(key);	//! MAY FAIL: memory
	} catch (std::bad_alloc& e){ 
		throw e; // throw std::bad_alloc	//TODO: Catch in player_smanager.
	}
	if(this->root == nullptr) {
		delete temp_key_find;
		throw NodeDosentExist();			//TODO: Catch. probably will never test on this. 
	}
	AvlNode<T>* ret_node = this->root->search(temp_key_find);
	if(ret_node == nullptr)
		throw NodeDosentExist();
	else
	return ret_node;
}

/**
 * @brief removes the node with the given key from the tree
 * @throw Empty() if the tree is empty
 * @throw DoesntExist if the node with the given key doesnot exist
 * @param key - the key to remove. 
 */
template<class T>
void AvlTree<T>::remove(T key){
	T* temp_key = new T(key);	//! MAY FAIL: memory
	if(this->root == nullptr) {
		throw Empty();			//TODO: Catch.
	}
	if(this->search(key) == nullptr){
		throw DoesntExist();	//TODO: Catch.
	} else { // key is surely inside the tree
		this->root = this->root->remove(temp_key);
	}
	size--;
}


/**
 * @brief inOrder print to the stdout
 * 
 * @param root - the root of the tree. 
 */
template<class T>
void AvlTree<T>::inOrder(){
	if (this->root == nullptr) {
		return;	// empty tree, should we throw exception if it's empty?
	}
	this->root->inOrder();
	
} 

/**
 * @brief 
 * 
 * @tparam T 
 */
template<class T>
void AvlTree<T>::inOrderReverse(){
	if (this->root == nullptr) {
		return;	// empty tree, should we throw exception if it's empty?
	}
	this->root->inOrderReverse();
	
} 

/**
 * @brief removes all nodes from the tree
 * 
 * @tparam T the type of the data stored in the nodes.
 */
template<class T>
void AvlTree<T>::clearTree(){
	if (this->root == nullptr) {
		return;	// empty tree, should it throw exception Empty?
	}
	this->root->clearAll();
	delete this->root;
	this->root =nullptr;
	this->size = 0;
} 

template <class T>
int AvlTree<T>::getSize() const{
	return this->size;
}

template <class T>
void AvlTree<T>::setRootNode(AvlNode<T>* new_root){
	this->root = new_root;
}

template <class T>
AvlNode<T>* AvlTree<T>::getMaxNode()
{
	return this->root->getMaxNode();
}




#endif