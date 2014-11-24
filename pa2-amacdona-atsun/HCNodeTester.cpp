/*
 * Huffman Coding - PA 2 CSE 100
 *   by Aidan Macdonald <amacdona@ucsd.edu>
 *      Andrew Tsun <atsun@ucsd.edu>
 * 
 * 
 * 
 */

#include "Tester.hpp"
#include "HCNode.hpp"

int main(){

    HCNode a(1, (byte)'a'); 
    HCNode b(2, (byte)'b');
    HCNode c(2, (byte)'c'); 
    
    cout << "Testing < functionality of HCNode: Different counts..." << endl; 
    EXEC(Tester::assert( a<b, "Node A(1,'a') is not less than Node B(2, 'a')");)
    cout << "Testing < functionality of HCNode: Same counts... " << endl; 
    EXEC(Tester::assert( b<c, "Node B(2,'b') is not less than Node C(2,'c')");)

    return 0; 
}
