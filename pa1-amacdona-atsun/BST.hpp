/* 
 * Binary Search Tree - Programming Assignment 1
 *  by Aidan Macdonald
 *     Andrew Tsun
 * 
 * Major class template implementation. 
 * 
 * 
 */

#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <utility> // for std::pair

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or nullptr if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;

  bool del(BSTNode<Data> *cur) {
    if (cur == nullptr)
      return false;

    this->del(cur->right);
    this->del(cur->left);
    
    delete cur;
    return true;
  }

public:

  /** iterator is an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(nullptr), isize(0)  {
  }


  /** Default destructor.
   *  It is virtual, to allow appropriate destruction of subclass objects.
   *  Delete every node in this BST.
   */
  virtual ~BST() {
    this->clear();
  }

  /** Insert a Data item in the BST.
   *  Return a pair, with the pair's first member set to an
   *  iterator pointing to either the newly inserted element
   *  or to the equivalent element already in the set.
   *  The pair's second element is set to true
   *  if a new element was inserted or false if an
   *  equivalent element already existed.
   */  
  virtual std::pair<iterator,bool> insert(const Data& item) {
    BSTNode<Data>* current = this->root;
    
    while (current != nullptr) {
      // If item already exists
      if (current->data == item)
	return std::pair<iterator,bool>(iterator(current),
				         false); // Exists
      
      // If item is less than current node. 
      else if (current->data > item) {
	if (current->left == nullptr){ // Left Insert
	  current->left = new BSTNode<Data>(item);
	  current->left->parent = current;
	  this->isize++;
          return std::pair<iterator, bool>(iterator(current->left),
					   true);
        }
	else{
	  current = current->left; 
        }  
      } // END IF LESSER CLAUSE

      // If item is greater than current node. 
      else{
        if (current->right == nullptr){ // Left Insert
	  current->right = new BSTNode<Data>(item);
	  current->right->parent = current;
	  this->isize++;
	  return std::pair<iterator, bool>(iterator(current->right),
					   true);
	}
	else{
	  current = current->right;
	}
      } // END IF GREATER CLAUSE
    } // END WHILE
    
    this->root = new BSTNode<Data>(item);
    this->isize++;
    return std::pair<iterator, bool>(iterator(this->root), true);
  } // END INSERT


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or the end
   *  iterator if the item is not in the BST.
   */
  iterator find(const Data& item) const {
    for (BSTNode<Data> *cur = this->root;
	 cur != nullptr;
	 cur = (item < cur->data ? cur->left : cur->right)) {
      if (cur->data == item)
	return typename BST<Data>::iterator(cur);
    }
    
    return this->end();
  }

  
  /** Return the number of items currently in the BST.
   */
  unsigned int size() const {
    return this->isize;
  }

  /** Remove all elements from this BST, and destroy them,
   *  leaving this BST with a size of 0.
   */
  void clear() {
    this->del(this->root);
    this->root = nullptr;
    this->isize = 0;
  }

  /** Return true if the BST is empty, else false.
   */
  bool empty() const {
    return (this->size() == 0);
  }

  /** Return an iterator pointing to the first item in the BST.
   */
  iterator begin() const {
    BSTNode<Data>* next;
    
    for (next = this->root;
	 next->left != nullptr;
	 next = next->left);
    return next;

    return typename BST<Data>::iterator(next);
  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(nullptr);
  }

  

 };


#endif //BST_HPP
