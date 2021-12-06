#ifndef AVLNODE
#define AVLNODE

#include <assert.h>
#include <iostream>

const int EMPTY_HEIGHT = 0;
const int LEAF_HEIGHT = 0;
const int L_ROTATE = 2;
const int R_ROTATE = -2;

template<class T> 
class AvlNode{
/***************************************************************************/
	T *key;
	int height;
	AvlNode* parent;
	AvlNode* left;
	AvlNode* right;
/***************************************************************************/
	AvlNode<T>* lrRotate();
	AvlNode<T>* llRotate();
	AvlNode<T>* rlRotate();
	AvlNode<T>* rrRotate();
	bool isTheLeftSon();
	bool isTheRightSon();
	bool hasLeftSon();
	bool hasRightSon();
	bool hasOnlyOneSon();
	bool hasTwoSon();
	AvlNode<T>* balanceTree();		


	public:
		AvlNode();
		AvlNode(T* key, AvlNode<T>* parent);
		~AvlNode();
		void clearAll();				// Deletes the sub-tree beneath the root (with the root)
		int getHeight() const;			
		int getBalanceFactor();
		int getLeftHeight() const;
		int getRightHeight() const;
		void updateHeight(); 	
		int max(int a, int b);
		void inOrder();
		void inOrderReverse();
		bool isLeaf();
		void setLeftSon(AvlNode<T>* new_son);
		void setRightSon(AvlNode<T>* new_son);
		void setHeight(int h);
		void setKey(T* new_key);
		AvlNode<T>* getLeftSon();
		AvlNode<T>* getRightSon();
		AvlNode<T>* getParent();
		AvlNode<T>* insert(T* key_add);	
    	AvlNode<T>* remove(T* key_remove);
		AvlNode<T>* search(T* key_find);
		T* getKey();
		AvlNode<T>* removeNode(); 
		AvlNode<T>* getMinNode();
		AvlNode<T>* getMaxNode();

};

template<class T> 
AvlNode<T>::AvlNode(T* key, AvlNode<T>* parent) : key(key), parent(parent)
{
	this->height = LEAF_HEIGHT;
	this->left = nullptr;
	this->right = nullptr;
}

template<class T> 
AvlNode<T>::~AvlNode()
{
	if(this->key != nullptr){
		delete this->key;
		this->key = nullptr;
	}
}


/* finds out is 'this' node is a left son to a node
	true - if the parent has a left pointer to me
	false - if the parent has no left pointer to me or 'this' is the root
 */
template<class T> 
bool AvlNode<T>::isTheLeftSon(){
	if(this->parent == nullptr ){
		return false; 
	} else if(this->parent->left != nullptr && this->parent->left->getKey() == this->getKey()){	//
		return true;
	} else return false; 
}


/* finds out is 'this' node is a right son to a node
	true - if the parent has a right pointer to me
	false - if the parent has no right pointer to me or 'this' is the root
 */
template<class T> 
bool AvlNode<T>::isTheRightSon()
{
	if(this->parent == nullptr )
	{
		return false; 
	}
	else if(this->parent->right != nullptr && this->parent->right->getKey() == this->getKey())
	{
		return true;
	}
	else return false; 
}


/* Checks if the node a left son
true - if it does
false - does not
 */
template<class T> 
bool AvlNode<T>::hasLeftSon()
{
	return this->left ? true : false; 
}

/* Checks if the node a right son
true - if it does
false - does not
 */
template<class T> 
bool AvlNode<T>::hasRightSon()
{
	return this->right ? true : false; 
}

template<class T> 
bool AvlNode<T>::hasOnlyOneSon()
{
	return ((this->hasLeftSon() == true && this->hasRightSon() == false) || (this->hasLeftSon() == false && this->hasRightSon() == true));
}

template<class T> 
bool AvlNode<T>::hasTwoSon(){
	return (this->hasLeftSon() == true && this->hasRightSon() == true);
}

template<class T> 
void AvlNode<T>::clearAll()	{		// review this function to understand better

	if(this->left != nullptr){
		this->left->clearAll();
		delete left;
		left = nullptr;
	}
	if(this->right != nullptr){
		this->right->clearAll();
		delete right;
		right = nullptr;
	}
}

template<class T> 
int AvlNode<T>::getHeight() const {
	return this->height;
}

template<class T>
T* AvlNode<T>::getKey() {
	return this->key;		// Maybe "&this->key" instead? A PLACE FOR BUGS
}

template<class T>
int AvlNode<T>::getLeftHeight() const {
	if(this->left == nullptr){
		return EMPTY_HEIGHT;
	}
	return this->left->getHeight() + 1;
}

template<class T>
int AvlNode<T>::getRightHeight() const {
	if(this->right == nullptr){
		return EMPTY_HEIGHT;
	}
	return this->right->getHeight() + 1;
}

template<class T>
int AvlNode<T>::getBalanceFactor(){
	this->updateHeight();
	return (this->getLeftHeight() - this->getRightHeight());
}

/* Updates the height of the sub-tree passed by this. Does not update the whole tree */
template<class T>
void AvlNode<T>::updateHeight() {
	this->height = max(this->getLeftHeight(),this->getRightHeight()); 
}

template<class T>
AvlNode<T>* AvlNode<T>::getLeftSon(){
	return this->left;
}

template<class T>
AvlNode<T>* AvlNode<T>::getRightSon(){
	return this->right;
}

template<class T>
AvlNode<T>* AvlNode<T>::getParent(){
	return this->parent;
}

/* Inserts node into the tree in an AVL fashion, thus inkoving the rotations if ones are needed. ASSUMES THT THERE IS NO NODE
	WITH THE SAME KEY
@param: key_add - a point of the T* data of the newly added node.
return value - the root of the new tree after the insertion and the rotations.
 */
template<class T>
AvlNode<T>* AvlNode<T>::insert(T* key_add){

	if(*key_add < *(this->key)){
		if(this->left == nullptr){
			try{
				this->left = new AvlNode<T>(key_add, this);			//! MAY FAIL: memory
			} 	catch (std::bad_alloc& e){
				throw e;
			}
		}
		else{
			this->left->insert(key_add);
		}
	}
	else if(*key_add > *(this->key)) {
		if(this->right == nullptr) {
			try {
				this->right = new AvlNode<T>(key_add , this);		//! MAY FAIL: memory
			} 	catch (std::bad_alloc& e){
				throw e;
			}
		} 
		else {
			this->right->insert(key_add);
		}
	}
	return this->balanceTree();	
}

template<class T>
AvlNode<T>* AvlNode<T>::llRotate(){
	AvlNode<T>* temp_left = this->left; 	// saves A
	this->left = this->left->right;			// B left son now points to Ar
	if(this->left != nullptr){				// parent of Ar is updated.
		this->left->parent = this;
	}
	temp_left->right = this;
	temp_left->parent = this->parent;
	// Updating the parent of the current offended BF node to point to the new root of the sub-tree
	if(this->parent != nullptr){
		if(this->parent->left != nullptr && this->parent->left->getKey() == this->getKey()){
			this->parent->left = temp_left;
		}
		else{
			this->parent->right = temp_left;
		}
	}
	this->parent = temp_left;		// this->parent shall not be nullptr in case there's more trees above to cover.
	temp_left->updateHeight();
	this->updateHeight();
	// THIIS SECTION IS FOR DEBUG ONLY
	//assert(temp_left->getBalanceFactor() != -2 && temp_left->getBalanceFactor() != 2 );
	//assert(this->getBalanceFactor() != -2 && this->getBalanceFactor() != 2 );
	// END OF SECTION
	return temp_left;
}

template<class T>
AvlNode<T>* AvlNode<T>::rrRotate()
{
	AvlNode<T>* temp_right = this->right; 	// saves A
	this->right = this->right->left;		// B right son now points to Al
	if(this->right != nullptr)				// parent of Al is updated.
	{
		this->right->parent = this;
	}
	temp_right->left = this;
	temp_right->parent = this->parent;
	
	// Updating the parent of the current offended BF node to point to the new root of the sub-tree
	if(this->parent != nullptr){
		if(this->parent->left != nullptr && this->parent->left->getKey() == this->getKey()) // if B is the left son
		{
			this->parent->left = temp_right;
		}
		else{
			this->parent->right = temp_right;
		}
	}
	this->parent = temp_right;		// this->parent shall not be nullptr in case there's more trees above to cover.
	this->updateHeight();
	temp_right->updateHeight();
	return temp_right;
}

template<class T>
AvlNode<T>* AvlNode<T>::lrRotate()
{
	/*
	AvlNode<T>* A_node = this->left;
	AvlNode<T>* B_node = this->left->right;
	AvlNode<T>* C_node = this;
	AvlNode<T>* B_node_left_subtree = this->left->right->left;
	AvlNode<T>* B_node_right_subtree = this->left->right->right;
	B_node->parent = this->parent;
	if(this->parent != nullptr){	// if the parent is nullptr we'll update the new tree rot by return
		if(B_node->isTheLeftSon()){
			this->parent->left = B_node;
		} else {
			this->parent->right = B_node;
		}
	}
		
	B_node->right = C_node;
	C_node->parent = B_node;

	B_node->left = A_node;
	A_node->parent = B_node;

	A_node->right = B_node_left_subtree; 
	if(B_node_left_subtree){
		B_node_left_subtree->parent = A_node;
	}
	C_node->left = B_node_right_subtree;
	if(B_node_right_subtree){
		B_node_right_subtree->parent = C_node;
	}
	A_node->updateHeight();
	C_node->updateHeight();
	B_node->updateHeight();
	return B_node;
	*/
	this->left->rrRotate();
	return this->llRotate();
}

template<class T>
AvlNode<T>* AvlNode<T>::rlRotate(){
	this->right->llRotate();
	return this->rrRotate();
}

/* 
	Returns the tree's new root
 */
template<class T>
AvlNode<T>* AvlNode<T>::balanceTree(){ // in the debug check if it is entering recursiving few times
	AvlNode<T>* temp_iterator = this; 	// Maybe start from this->parent? 
	AvlNode<T>* new_tree_root = this; 
	while(temp_iterator != nullptr){
		if(temp_iterator->getBalanceFactor() == L_ROTATE){	// means LR or LL rotation
		
			if(temp_iterator->getLeftSon()->getBalanceFactor() >= 0 )
			{
			temp_iterator->llRotate();
			} else if (temp_iterator->getLeftSon()->getBalanceFactor() == -1 )
			{
				temp_iterator->lrRotate();
			}
		}
		else if(temp_iterator->getBalanceFactor() == R_ROTATE){	// mean RR or RL rotation
				if(temp_iterator->getRightSon()->getBalanceFactor() <= 0){
					temp_iterator->rrRotate();
				}
				else if(temp_iterator->getRightSon()->getBalanceFactor() == 1){
				temp_iterator->rlRotate();
			}
		}
		new_tree_root = temp_iterator;
		temp_iterator = temp_iterator->parent; 	
	}
	return new_tree_root;
}	

template<class T>
AvlNode<T>* AvlNode<T>::getMinNode()
{
	AvlNode<T>* min_node = this;
	while(min_node->left != nullptr)
	{
		min_node = min_node->getLeftSon();
	}
	return min_node;
}

template<class T>
AvlNode<T>* AvlNode<T>::getMaxNode()
{
	AvlNode<T>* max_node = this;
	while(max_node->right != nullptr)
	{
		max_node = max_node->getRightSon();
	}
	return max_node;
}


/**
 * @brief removes 'this' and updates the parents left and right sons accordingly
 * removeNode() is called only by remove()
 * Does not balance the WHOLE tree after removal, only the sub tree! The update for the whole is done in reomve() as recursion ends.
 * @tparam T 
 * @return AvlNode<T>* new subtree root, balanced.
 */
template<class T>
AvlNode<T>* AvlNode<T>::removeNode(){
	AvlNode<T>* temp_this = this; // for backup up 
	if(this->hasLeftSon() == false && this->hasRightSon() == false) { // 'this' is a leaf, we just need to remove him. Regardless if it is a root.
		if(this->isTheLeftSon()) { // 'this' node is a leaf and the left son of a parent
			this->parent->left = nullptr; 
		}
		if(this->isTheRightSon()) { // this, is and a leaf and is the right son
			this->parent->right = nullptr;
		}
		temp_this = this->parent;
		delete this;
		return temp_this;
	} 
	// Deletion algorithm STEP 2: Assigment of a son to the parent
	else { // not a leaf
		if(this->hasOnlyOneSon()) { 	// not a leaf, has one son atleast. 
			if(this->parent == nullptr){
				if(this->hasLeftSon()){
					this->left->parent = nullptr;
					temp_this = this->left; 		//!! WAS NOT HERE
					if(temp_this->parent == nullptr){
					temp_this->updateHeight();			//this if is for when the deleted root has only one son which becomes the root.
					} else {
					temp_this->parent->updateHeight();						
					}
					delete this;
					return temp_this;	
				} else if(this->hasRightSon()){
					temp_this = this->right;		//!! WAS NOT HERE
					this->right->parent = nullptr;
					if(temp_this->parent == nullptr){	// this if is for when the deleted root has only one son which becomes the root.
					temp_this->updateHeight();						
					} else {
					temp_this->parent->updateHeight();						
					}
					delete this;	
					return temp_this;	
				}
			}
			if(this->hasRightSon())	{		//he got only right son and it is the only son
				this->right->parent = this->parent;
				if(this->isTheRightSon()) {
					this->parent->right = this->right;	
					
				}
				else if(this->isTheLeftSon()) {
					this->parent->left = this->right;
				}
			temp_this = temp_this->right;	
			temp_this->parent->updateHeight();
			delete this;
			return temp_this;
			}
			else if(this->hasLeftSon()){
				this->left->parent = this->parent;
				if(this->isTheRightSon()){
					this->parent->right = this->left;
				}
				else if(this->isTheLeftSon()){
					this->parent->left = this->left;
				}
				temp_this = temp_this->left;
				temp_this->parent->updateHeight();
				delete this;
				return temp_this;
			}
		}
	else {
		// got 2 sons
		//swapping between min and this;
		AvlNode<T>* min_node = this->right->getMinNode();
		bool adjacent = false;
		AvlNode<T>* min_node_right = min_node->right; 	// can also be null
		AvlNode<T>* min_node_parent = min_node->parent;	// will never be null
		/* Special case */
		if(this->right->getKey() == min_node->getKey()){
			adjacent = true;
			min_node->right = this;
		}
		else {
			min_node->right = this->right;	// copied from line 505
			this->right->parent = min_node;
		}
		/* updating min_node pointers and its new sons pointers */
		min_node->left = this->left;
		this->left->parent = min_node;
		/* updating the min_node new sons parent pointers, if the parent is nullptr, which means the parent is the root 
		the updating is done by the reutrn value and not here (in the case Min_node is the new root)*/
		min_node->parent = this->parent;
		if(this->parent != nullptr){	
			if(this->isTheLeftSon()){
				this->parent->left = min_node;
			} else if(this->isTheRightSon()){
				this->parent->right = min_node;
			}
		}
		/* Updating 'this's new pointers and its new sons pointers */
		this->right = min_node_right;
		if(this->right != nullptr){ // if min_node->right parent exist, update them. 
			this->right->parent= this;
		}
		this->left = nullptr;	//because its in the min place
		if(adjacent == true){
			this->parent = min_node;
			
		} else {
			min_node_parent->left = this;
			this->parent = min_node_parent;
		}
		min_node_parent->updateHeight();
		this->removeNode();	// now 'this' is removed, maybe as a leaf and maybe as a father to one right son.
		min_node->updateHeight(); // the parent of the left subtree's root. 
		return min_node;	// min node is the new subtree root.
	}
}
return nullptr;  //note:  we should never get here. The return here is for the compiler to shut up. 
}

/**
 * @brief the function removes the node with the same key value as passed in the @key_remove param. 
the function ASSUMES that the wanted value is in the node or in its subtrees, since the check for the existance of
the vaulue is done before-hand in the remove function of the AVLTree_remove!
 * ASSUMES that tree is not empty. 
 * @tparam T
 * @param key_remove - a pointer to the value we wish to remove.
 * @return AvlNode<T>* Returns the new tree's root after balancing it.
 * */
template<class T>
AvlNode<T>* AvlNode<T>::remove(T* key_remove){
	AvlNode<T>* new_subtree = this; // the subtree after removal of 'this'
	AvlNode<T>* temp_parent = this->parent; // the subtree after removal of 'this'
	AvlNode<T>* temp_iterator = this->parent;   // for later usage for upstream update.
	if(*(this->key) < *key_remove){
			this->right->remove(key_remove);
	} else if((*this->key) > *key_remove){
		this->left->remove(key_remove);
	} else { // found the key
		new_subtree = this->removeNode(); 
		temp_iterator = new_subtree;
		while(temp_iterator != nullptr){
			temp_iterator->updateHeight();	// imo - temp_iterator->parent should be updated.
			temp_iterator = temp_iterator->parent;
		}
	}
	if(new_subtree == nullptr && temp_parent == nullptr){ // root, is a leaf and is removed OR a leaf with a parent
		return nullptr;
	} else {
		return new_subtree->balanceTree(); // not optimal for perfomance but works (some calls will be futile, O(1) times)
	}
}

/**
 * @brief searches for a key inside the AVL tree
 *
 * @param key_find - the key
 * @return AvlNode<T>* - a pointer to the node if found. NULLPTR is not found.
 */
template<class T>
AvlNode<T>* AvlNode<T>::search(T* key_find)
{
	AvlNode<T>* node_iterator = this; 
	if(node_iterator == nullptr){ 	// The stop condition that we have arrived at a leaf
		return nullptr;
	}
	while(node_iterator != nullptr)	{
		if(*(node_iterator->getKey()) == *key_find){
			return node_iterator;
		}
		else if( *(node_iterator->getKey()) > *key_find){
			node_iterator = node_iterator->left;
		} else if( *(node_iterator->getKey()) < *key_find){
			node_iterator = node_iterator->right;
		}
	}
	return node_iterator;
}

template<class T>
int AvlNode<T>::max(int a, int b){
	if(a > b) return a;
	if(a < b) return b;
	return a;
}

template<class T>
void AvlNode<T>::inOrder(){
	if(this == nullptr) return;
	this->left->inOrder();
	std::cout << (*(this->key))  << std::endl;
	this->right->inOrder();
}

template<class T>
void AvlNode<T>::inOrderReverse(){
	if(this == nullptr) return;
	this->right->inOrderReverse();
	std::cout << *(this->key) << std::endl;
	this->left->inOrderReverse();

}

template<class T>
void AvlNode<T>::setRightSon(AvlNode<T>* new_son){
	this->right = new_son;
}

template<class T>
void AvlNode<T>::setLeftSon(AvlNode<T>* new_son){
	this->left = new_son;
}

template<class T>
void AvlNode<T>::setHeight(int h){
	this->height = h;
}

template<class T>
bool AvlNode<T>::isLeaf(){
	return (this->left == nullptr && this->right == nullptr);
}

template<class T>
void AvlNode<T>::setKey(T* new_key){
	this->key = new_key;
}

#endif 