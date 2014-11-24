/*
 * Huffman Coding - PA 2 CSE 100
 *   by Aidan Macdonald <amacdona@ucsd.edu>
 *      Andrew Tsun <atsun@ucsd.edu>
 * 
 * 
 * 
 */

#include "Tester.hpp"

bool Tester::assert(bool condition, const string& err_msg){
    if(!condition)
        cout << "ERROR: " << err_msg; 
}

bool Tester::assert(bool condition, stringstream& err_msg){
    assert(condition, err_msg.str());
}

