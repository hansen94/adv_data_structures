
/*
 * Huffman Coding - PA 2 CSE 100
 *   by Aidan Macdonald <amacdona@ucsd.edu>
 *      Andrew Tsun <atsun@ucsd.edu>
 * 
 * Implementation of Huffman Tree
 * 
 */

#include "HCTree.hpp"


HCTree::~HCTree(){
    delTree(root);
}

void HCTree::delTree(HCNode* curr){
    if (curr == (HCNode*)0)
        return;
    delTree(curr->c0);
    delTree(curr->c1);
    delete curr; 
}

void HCTree::build(const vector<int>& freqs){
  priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq; 
   
   //Add all characters with non-zero frequencies to the priority queue.
   for(unsigned int i = 0; i < freqs.size(); i++){
     HCNode* leaf = new HCNode(freqs[i], (byte)i); // Make new leaf 
        if (i >= leaves.size()) {

        } else {
            leaves[i] = leaf; // Overwrite corr. null leaf in leaves. 
        }
        if (freqs[i] > 0) // Push non-0 frequency leaves to priority queue
            pq.push(leaf);  
	else // Delete leaf if it isn't being used. 
	  delete leaf;
   }

   //Build Huffman tree. 
   while(pq.size() > 1){
     // Join 2 smallest trees into larger tree
        HCNode* child0 = pq.top(); 
	pq.pop();
        HCNode* child1 = pq.top();
	pq.pop();
        int count = child0->count + child1->count; 
        HCNode* parent = new HCNode(count, (byte)0, child0, child1);
        // Set children to point to new parent tree. 
        child0->p = parent;
        child0->isChild0 = true; 
        child1->p = parent;
        // Push new tree onto the stack. 
        pq.push(parent); 
   }

   //Tree left in priority queue IS the Huffman tree
   if (pq.size() >= 1) {
     root = pq.top(); 
   }
}

void HCTree::encode(byte symbol, ofstream& out) const{
    if(leaves[(int) symbol]->count == 0){
        return; 
    }
    // Write code to file as traversing Huffman tree from leaf to root
    string code(""); 
    for(HCNode* curr = leaves[(int)symbol];
	curr->p != (HCNode*) 0; 
        curr = curr->p) {            
      code = (curr->isChild0 ? "0" : "1") + code;
    }

    if (leaves[(int)symbol] == this->root)
      code += "0";

    out << code; 
}

void HCTree::encode(byte symbol, BitOutputStream& out) const{
    if(leaves[(int) symbol]->count == 0){
        return; 
    }
    // Write code to file as traversing Huffman tree from leaf to root
    string code(""); 
    for(HCNode* curr = leaves[(int)symbol];
	curr->p != (HCNode*) 0; 
        curr = curr->p) {            
      code = (curr->isChild0 ? "0" : "1") + code;
    }

    if (leaves[(int)symbol] == this->root)
      code += "0";

    for (size_t i=0;i<code.size();i++)
      out.writeBit((code[i] == '1' ? 1 : 0));
}


int HCTree::decode(ifstream& in) const {
    HCNode* curr = root;
    unsigned char c;
    // Traverse tree from root to leaf to get symbol.

    while(curr->c0 != (HCNode*)0 && curr->c1 != (HCNode*)0){
        in >> c; 

        if (c == '0'){
            curr = curr->c0;
        }
        else{
            curr = curr->c1; 
        }
        //curr = (c == '0' ? curr->c0 : curr->c1); 
    }
    if (curr == this->root)
      in >> c;

    // Output symboli
    return (int)curr->symbol; 
}

int HCTree::decode(BitInputStream& in) const {
    HCNode* curr = root;
    if (curr == (HCNode*)0)
      return -1;

    int c;
    // Traverse tree from root to leaf to get symbol.

    while(curr->c0 != (HCNode*)0 && curr->c1 != (HCNode*)0){
      c = in.readBit();

        if (c == 0){
            curr = curr->c0;
        }
        else{
            curr = curr->c1; 
        }
        //curr = (c == '0' ? curr->c0 : curr->c1); 
    }
    if (curr == this->root)
      c = in.readBit();

    // Output symboli
    return (int)curr->symbol; 
}
