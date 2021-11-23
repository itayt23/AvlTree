#ifndef AVLNODE
#define AVLNODE

#include <assert.h>

#include "math.h"

const int EMPTY_HEIGHT = -1;
const int LEAF_HEIGHT = 0;
const int L_ROTATE = 2;
const int R_ROTATE = -2;


template<class T> 
class AvlNode
{
	T *key;
	int height;
	AvlNode* parent;
	AvlNode* left;
	AvlNode* right;

	public:
	AvlNode() = delete;
	AvlNode(T* key, AvlNode<T>* parent);
	~AvlNode();

	void clearAll();				// Deletes the sub-tree beneath the root (with the root)
	int getHeight() const;			
	int getBalanceFactor() const;
	int getLeftHeight() const;
	int getRightHeight() const;
	void updateHeight(); 	

	/* 
	Checks the newly inserted node's parents (throguht the path it was inserted) and invokes the RL, RR, RL, LL rotations
	balanceAll is invokes by the insert and remove functions.
	 */
	AvlNode<T> *balanceTree();		
	AvlNode<T> *lrRotate();
	AvlNode<T> *llRotate();
	AvlNode<T> *rlRotate();
	AvlNode<T> *rrRotate();

	AvlNode<T>* insert(T* key_add);		// might be in AvlTree.h file
    AvlNode<T>* remove(T* key_remove);	// might be in AvlTree.h file
    AvlNode<T>* search(T* key_find);	// might be in AvlTree.h file


	
	T* getKey();
	AvlNode<T>* getLeftSon();
	AvlNode<T>* getRightSon();
	AvlNode<T>* getParent();

};

template<class T> 
AvlNode<T>::AvlNode(T* key, AvlNode<T>* parent) : key(key), parent(parent)
{
	this->height = LEAF_HEIGHT;
	//this->parent = nullptr;
	this->left = nullptr;
	this->right = nullptr;
}

template<class T> 
AvlNode<T>::~AvlNode()
{
	if(this->key != nullptr)
	{
		delete this->key;
		this->key = nullptr;
	}
}

template<class T> 
void AvlNode<T>::clearAll()			// review this function to understand better
{
	if(this->left != nullptr)
	{
		this->left->clearAll();
		delete left;
		left = nullptr;
	}
	if(this->right != nullptr)
	{
		this->right->clearAll();
		delete right;
		right = nullptr;
	}
}

template<class T> 
int AvlNode<T>::getHeight() const
{
	return this->height;
}

template<class T>
T* AvlNode<T>::getKey()
{
	return this->key;		// Maybe "&this->key" instead? A PLACE FOR BUGS
}

template<class T>
int AvlNode<T>::getLeftHeight() const
{
	if(this->left == nullptr)
	{
		return EMPTY_HEIGHT;
	}
	return this->left->getHeight() + 1;
}

template<class T>
int AvlNode<T>::getRightHeight() const
{
	if(this->right == nullptr)
	{
		return EMPTY_HEIGHT;
	}
	return this->right->getHeight() + 1;
}

template<class T>
int AvlNode<T>::getBalanceFactor() const
{
	return (this->getLeftHeight() - this->getRightHeight());
}

template<class T>
void AvlNode<T>::updateHeight() 
{
	this->height = 1 + fmax(this->getLeftHeight(),this->getRightHeight())); 
}

template<class T>
AvlNode<T>* AvlNode<T>::getLeftSon()
{
	return this->left;
}

template<class T>
AvlNode<T>* AvlNode<T>::getRightSon()
{
	return this->right;
}

template<class T>
AvlNode<T>* AvlNode<T>::getParent()
{
	return this->parent;
}

/* Inserts node into the tree in an AVL fashion, thus inkong the rotations if ones are needed.
@param: key_add - a point of the T* data of the newly added node.
return value - the root of the new tree after the insertion and the rotations.
 */
template<class T>
AvlNode<T>* AvlNode<T>::insert(T* key_add)
{
	if(key_add < this->key)  //need to make operator < 
	{
		if(this->left == nullptr)
		{
			this->left = new AvlNode<T>(key_add, this);
		}
		else
		{
			this->left->insert(key_add);
		}
	}
	else if(key_add > this->key) //need to make operator > and maybe operator= 
	{
		if(this->right == nullptr)
		{
			this->right = new AvlNode<T>(key_add , this);
		} 
		else 
		{
			this->right->insert(key_add);
		}
	}
	else
	{
		return "NEED TO THROW EXCEPTION THAT THE NODE ALREADY EXIST";
	}
	return this->balanceTree();
	
}

template<class T>
AvlNode<T>* AvlNode<T>::llRotate()
{
	AvlNode<T>* temp_left = this->left; 	// saves A
	this->left = this->left->right;			// B left son now points to Ar
	if(this->left != nullptr)				// parent of Ar is updated.
	{
		this->left->parent = this;
	}
	temp_left->right = this;
	temp_left->parent = this->parent;
	
	// Updating the parent of the current offended BF node to point to the new root of the sub-tree
	if(this->parent != nullptr)
	{
		if(this->parent->left != nullptr && this->parent->left->getKey() == this->getKey())
		{
			this->parent->left = temp_left;
		}
		else
		{
			this->parent->right = temp_left;
		}
	}
	this->parent = temp_left;		// this->parent shall not be nullptr in case there's more trees above to cover.
	temp_left->updateHeight();
	this->updateHeight();
	// THIIS SECTION IS FOR DEBUG ONLY
	assert(temp_left->getBalanceFactor() != -2 && temp_left->getBalanceFactor() != 2 );
	assert(this->getBalanceFactor() != -2 && this->getBalanceFactor() != 2 );
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
	if(this->parent != nullptr)
	{
		if(this->parent->left != nullptr && this->parent->left->getKey() == this->getKey()) // if B is the left son
		{
			this->parent->left = temp_right;
		}
		else
		{
			this->parent->right = temp_right;
		}
	}
	this->parent = temp_right;		// this->parent shall not be nullptr in case there's more trees above to cover.
	temp_right->updateHeight();
	this->updateHeight();
	// THIIS SECTION IS FOR DEBUG ONLY
	assert(temp_right->getBalanceFactor() != -2 && temp_right->getBalanceFactor() != 2 );
	assert(this->getBalanceFactor() != -2 && this->getBalanceFactor() != 2 );
	// END OF SECTION
	return temp_right;
}

/* Can be executed by RR and LL rotation */
template<class T>
AvlNode<T>* AvlNode<T>::lrRotate()
{
	AvlNode<T>* temp_left = this->left;
	AvlNode<T>* temp_left_right = this->left->right;
	temp_left->right = temp_left_right->left;
	if(temp_left->right != nullptr)				// parent of Bl is updated.
	{
		temp_left->right->parent = temp_left;
	}
	temp_left_right->left=temp_left;
	temp_left->parent = temp_left_right;
	this->left = temp_left_right->right;
	if(temp_left_right->right != nullptr)				// parent of Bl is updated.
	{
		temp_left_right->right->parent = this;
	}
	temp_left_right->right = this; 
	// Updating the parent of the current offended BF node to point to the new root of the sub-tree
	if(this->parent != nullptr)
	{
		if(this->parent->left != nullptr && this->parent->left->getKey() == this->getKey()) // if B is the left son
		{
			this->parent->left = temp_left_right;
		}
		else
		{
			this->parent->right = temp_left_right;
		}
	}
	this->parent = temp_left_right;
	temp_left_right->updateHeight();
	temp_left->updateHeight();
	this->updateHeight();
	// ADD ASSERT HERE

	return temp_left_right;
}

template<class T>
AvlNode<T>* AvlNode<T>::rlRotate()
{
	this->right->llRotate();
	return this->rrRotate();
}


template<class T>
AvlNode<T>* AvlNode<T>::balanceTree()
{
	AvlNode<T>* temp_iterator = this; 	// Maybe start from this->parent? 
	AvlNode<T>* new_tree_root = this; 
	while(temp_iterator != nullptr)
	{
		if(temp_iterator->getBalanceFactor() == L_ROTATE)	// means LR or LL rotation
		{
			if(temp_iterator->getLeftSon()->getBalanceFactor() >= 0 )
			{
			temp_iterator->llRotate();
			} else if (temp_iterator->getLeftSon()->getBalanceFactor() == -1 )
			{
				temp_iterator->lrRotate();
			}
		}
		else if(temp_iterator->getBalanceFactor() == R_ROTATE)	// mean RR or RL rotation
		{
			if(temp_iterator->getRightSon()->getBalanceFactor() <= 0)
			{
				temp_iterator->rrRotate();
			}
			else if(temp_iterator->getRightSon()->getBalanceFactor() == 1)
			{
				temp_iterator->rlRotate();
			}
		}
		new_tree_root = temp_iterator;
		temp_iterator = temp_iterator->parent; 	
	}
	return new_tree_root;
}	



template<class T>
AvlNode<T>* AvlNode<T>::remove(T* key_remove)
{
	
}

template<class T>
AvlNode<T>* AvlNode<T>::search(T* key_find)
{
	AvlNode<T>* node_iterator = this; 
	if(node_iterator == nullptr)
	{
		return "EXCEPTION" // empty tree
	}
	while(node_iterator != nullptr)	{
		if(node_iterator->getKey() == key_find)
		{
			return node_iterator;
		}
		else if(node_iterator->getKey() > key_find)
		{
			node_iterator = node_iterator->left;
		}
		
		else if(node_iterator->getKey() < key_find)
		{
			node_iterator = node_iterator->right;
		}
	}
	throw std::exception; // not found! 
}

#endif 