/* 
 * Binary Search Tree - Programming Assignment 1
 *  by Aidan Macdonald
 *     Andrew Tsun
 * 
 * Class definition for nodes in a 
 * Binary search tree.
 * 
 */

#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>


/** This class template defines a node type for the BST container.
 *  Note that all members are public. So, the BST implementation should
 *  take care not to expose any BSTNode objects.
 */
template<typename Data>
class BSTNode {
protected:
  // Ascend up to the left and stop when
  // no more left parents exist
  BSTNode<Data>* leftAscend() {
    BSTNode<Data>* next;

    for (next = this;
	 next->parent != nullptr && 
	   // If the right child of the parent is next
	   // Then we are ascending left
	   next->parent->right == next;
	 next = next->parent);
    
    return next;
  }

  BSTNode<Data>* leftExtrema() {
    BSTNode<Data>* next;
    
    for (next = this;
	 next->left != nullptr;
	 next = next->left);
    return next;
  }

  BSTNode<Data>* rightExtrema() {
    BSTNode<Data>* next;
    
    for (next = this;
	 next->right != nullptr;
	 next = next->right);
    return next;
  }

public:

  /** Member variables. */
  BSTNode<Data>* parent;
  BSTNode<Data>* left;
  BSTNode<Data>* right;
  const Data data;  // the const Data in this node
  int info;  // variable used in advanced algorithms 

  /** Constructor.  Initialize a BSTNode with the given Data item,
   *  no parent, and no children.
   */
  BSTNode(const Data & d): data(d) {
    left = right = parent = nullptr;
  }

  /** Return the inorder successor of this BSTNode in a BST,
   *  or nullptr if none.
   *  PRECONDITION: this BSTNode is a node in a BST.
   *  POSTCONDITION:  the BST is unchanged.
   *  RETURNS: the BSTNode that is the inorder successor of this BSTNode,
   *  or nullptr if there is none.
   */ 
  BSTNode<Data>* successor() {
    // Case 1: Right subtree exists. 
    if (this->right != nullptr){
      return this->right->leftExtrema();
    }
    
    // All the following cases are for if right child does not exist. 
    // Case 2: No right child, no parent.
    if (this->parent == nullptr){
       return nullptr;  
    }

    // All following cases assume that a parent is present. 
    // Case 3: If this node is its parent's left child
    if (this == this->parent->left){
        return this->parent;
    } 

    // Case 4: This node is the right child of its parent.
    return this->leftAscend()->parent; 
  }
}; 

/** Overload operator<< to insert a BSTNode's fields in an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << std::setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << std::setw(10) << n.parent; // address of its parent
  stm << "; l:" << std::setw(10) << n.left;   // address of its left child
  stm << "; r:" << std::setw(10) << n.right;  // address of its right child
  stm << "; i:" << std::setw(10) << n.info;   // its info field
  stm << "; d:" << n.data;                    // its data field
  stm << ']';
  return stm;
}

#endif // BSTNODE_HPP
