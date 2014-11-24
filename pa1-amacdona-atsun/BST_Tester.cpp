/* 
 * Binary Search Tree - Programming Assignment 1
 *  by Aidan Macdonald
 *     Andrew Tsun
 * 
 * Tester file
 * 
 * 
 */

#include <iostream>  
#include <functional> 
#include <string>
#include <stdlib.h>
#include "BST.hpp"
#include "BSTIterator.hpp"
#include <sstream>
#include "BSTNode.hpp"

using namespace std; 
 
int main(){

    BST<int> tree; 
    
    auto assert_str = [](bool condition, string err_msg){
        if(!condition)
	    cout << "ERROR: " << err_msg << endl;
    };     

    auto assert_ss = [](bool condition, stringstream& err_msg){
        if(!condition)
	  cout << "ERROR: " << err_msg.str() << endl;
    };    

    auto insert = [&tree, &assert_ss](int i, int expected_size){
        cout << "Inserting " << i << "..." << endl;  
        tree.insert(i);
        stringstream err_msg; 
        err_msg << i << " has not been inserted ";
        assert_ss(tree.size() == expected_size, err_msg); 
    };                                

    // Init empty tree. 
    assert_str(tree.empty(), string("Tree is not empty"));
    // Fill with empty numer in nonconsec order. 
    // Assert that there is an increase in size. 
    cout << "Testing insertion..." << endl; 
    insert(1, 1);
    assert_str(!tree.empty(), string("Tree is empty"));
    insert(3, 2);
    insert(5, 3);
    insert(4, 4); 
    insert(2, 5);
    insert(6, 6);
    insert(9, 7);
    insert(7, 8);
    insert(8, 9); 
    insert(0, 10);
    cout << "[DONE]" << endl;
        
    // Test the beginning and end iterators.  
    cout << "Testing begin iterator..." << endl; 
    BST<int>::iterator begin = tree.begin(); 
    stringstream err_msg_1;
    err_msg_1 << "Beginning iterator points to " << *begin;
    assert_ss(*begin == 0, err_msg_1);
    cout << "[DONE]" << endl; 
    cout << "Testing end iterator..." << endl; 
    BST<int>::iterator end = tree.end();
    // assert_str(*end == nullptr, "End iterator doesn't point to nullptr.");
    cout << "[DONE]" << endl; 

    // Test find iterator. 
    int random = rand() % 10; 
    cout << "Testing find iterator for element \"" << random << "\" in tree..." << endl; 
    BST<int>::iterator inTree = tree.find(random);
    stringstream err_msg_notfound;
    err_msg_notfound << random << " has not been found."; 
    assert_ss(inTree != tree.end(), err_msg_notfound); 

    cout << "Testing find iterator for element \"11\" not in tree ..." << endl; 
    BST<int>::iterator notInTree = tree.find(11);
    assert_str(notInTree == tree.end(), string("11 has been erroneously found")); 

    // Test traversal. 
    // Despite nonconsec order, inorder traversal should print sorted order. 
    int i = 0; 
    cout << "Using iterator to print inorder traversal sequence... "; 
    for(BST<int>::iterator itr = tree.begin(); itr != tree.end(); itr++){
            stringstream err_msg_traversal;
            err_msg_traversal << i << " is not next in sequence, " << *itr << " is next in sequence instead."; 
            assert_ss(i == *itr, err_msg_traversal); 
            cout << " " << *itr << " "; 
            i++; 
    }; 
    cout << endl; 

    // Test clear function.
    tree.clear();  
    assert_str(tree.empty(), string("Tree is not empty"));
    for(int i = 0; i < 10; i++){
        stringstream err_msg_notEmpty;
        err_msg_notEmpty << i << " should not exist in the tree.";
        assert_ss(tree.find(i) == tree.end(), err_msg_notEmpty);
    }
    assert_str(tree.size() == 0, string("Tree size != 0")); 

    return 0; 
}

