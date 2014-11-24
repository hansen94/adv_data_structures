/*
 * Huffman Coding - PA 2 CSE 100
 *   by Aidan Macdonald <amacdona@ucsd.edu>
 *      Andrew Tsun <atsun@ucsd.edu>
 * 
 * 
 * 
 */

#include "HCTree.hpp"
#include "Tester.hpp"
#include <vector>

using namespace std; 

int main(){

  // Build the Huffman Tree on the following sequence: wowrodrwow
    cout << "Building Huffman Tree for testing... " << endl; 
    vector<int> frq(256,0); 
    frq[(int)((byte)'w')] = 4; 
    frq[(int)((byte)'o')] = 3;
    frq[(int)((byte)'r')] = 2;
    frq[(int)((byte)'d')] = 1;
    cout << "Frequencies: 'w' = 4, 'o' = 3, 'r' = 2, 'd' = 1" << endl; 
    HCTree tree; 
    EXEC(tree.build(frq);)
    cout << "[DONE]" << endl << endl; 

    // Create an output file with encoded words. 
    cout << "Creating output file, encoding string \"wordwor\"...";
    ofstream writeFile("HCTreeTester_output");
    if (!writeFile.good()){
      cerr << endl << "Cannot create output encoded file" << endl;
      return 1; 
    }

    ofstream stdout("/dev/stdout");

#define ENC(c)  stdout << "Encoded " << c << " to ";	\
  tree.encode((byte)c, stdout);			\
  stdout << std::endl;

#define ENCB(c) ENC(c);				\
  tree.encode((byte)c, writeFile);

    // Encode Letters

    ENCB('w');
    ENCB('o');
    ENCB('r');
    ENCB('d');
    ENCB('w');
    ENCB('o');
    ENCB('r');
    stdout.close();
    writeFile.close(); 
    cout << "[DONE]." << endl;
    
    // Decode the output file and print the results to screen.
    cout << "Reading output file..." << endl; 
    ifstream readFile("HCTreeTester_output");
    if (!readFile.good()){
      cerr << "Cannot read output encoded file" << endl;
      return 2;
    }

    while( ((int)readFile.peek()) != EOF){
        int decoded = tree.decode(readFile);
        cout << (byte) decoded; 
    }
    cout << endl << "[DONE]." << endl; 
    readFile.close(); 

    return 0; 
}
