/*
 * Huffman Coding - PA 2 CSE 100
 *   by Aidan Macdonald <amacdona@ucsd.edu>
 *      Andrew Tsun <atsun@ucsd.edu>
 * 
 * Implementation of Huffman Tree node
 * 
 */


#include "HCNode.hpp" 

bool HCNode::operator<(const HCNode& other){
  // If counts are equal, symbol is the tiebreaker.
    if (this->count == other.count)
        return this->symbol < other.symbol; 
    return this->count < other.count;  
}

bool comp(HCNode* one, HCNode* other) {
  return *one < *other;
}
