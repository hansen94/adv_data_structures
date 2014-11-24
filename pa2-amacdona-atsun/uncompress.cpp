/*
 * Huffman Coding - PA 2 CSE 100
 *   by Aidan Macdonald <amacdona@ucsd.edu>
 *      Andrew Tsun <atsun@ucsd.edu>
 * 
 * Main file for uncompress
 * 
 */


#include "HCTree.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <utility> 
#include <algorithm>
#include <iterator>

using namespace std; 


int main(int argc, char** argv){

    // Check for 3 arguments. If not, display usage message. 
    if (argc != 3){
        cerr << argv[0] << " called with incorrect arguments. " << endl;
        cerr << "Usage: " << argv[0] << " infile outfile" << endl; 
        return 1; 
    }

    // Check for same file for infile and outfile 
    if( string(argv[1]) == string(argv[2]) ){
        cerr << "infile and outfile must be different files" << endl; 
        cerr << argv[0] << " called with incorrect arguments. " << endl;
        cerr << "Usage: " << argv[0] << " infile outfile" << endl;   
        return 2;
    }  

    // Open infile and check for successful open. 
    ifstream readFile(argv[1], ios::binary); 
    if (!readFile){  
        //cerr << "Error opening \"" << argv[1] << "\". " << endl;
        cerr << "Error opening \"0\"." << endl; 
        return 3; 
    }

    // Open up output file for writing, check for successful open. 
    ofstream writeFile(argv[2]); 
    if (!writeFile){
        //cerr << "Error opening \"" << argv[2] << "\"." << endl;
        cerr << "Error opening \"0\"." << endl; 
        return 4; 
    }   

    // Recover size of compressed file. 
    readFile.seekg(0, ios_base::end);
    int inFile_end = readFile.tellg();
    readFile.seekg(0, ios_base::beg);
    int inFile_beg = readFile.tellg();                        
    int inFile_size = inFile_end - inFile_beg; 

    // Generate frequency vector from encoded frequency table
    cerr << "Reading header from file \"" << argv[1] << "\"... "; 
    BitInputStream bis(readFile); 

#define CHKEOF(to, from) \
    if ( (to = from) == -1) { \
        cerr << " Problem: EOF while reading header." << endl; \
        return 5;\
    }       
    
    int exp_size;
    CHKEOF(exp_size, bis.readInt());
    int unique; 
    CHKEOF(unique, bis.readInt());
    vector<int> frq(256, 0); 
    for (int i = 0; i < unique; i++){
        int symbol;
        CHKEOF(symbol, bis.readByte()); 
        CHKEOF(frq[(size_t)symbol], bis.readInt()); 
    }
    cerr << "done." << endl;
#undef CHKEOF

    cerr << "Uncompressed file will have " << unique << " unique symbols ";
    cerr << "and size " << exp_size << " bytes." << endl;
    
    // Build Huffman tree
    cerr << "Building Huffman code tree... ";
    HCTree tree;
    tree.build(frq); 
    cerr << "done." << endl; 

    // Decode from the tree.  
    cerr << "Writing to file \"" << argv[2] << "\"... "; 

    
    int written = 0;
    while( ((int)readFile.peek()) != EOF || written < exp_size) {
        int symbol = tree.decode(bis);
	if (symbol < 0) // Case where tree.root == NULL
	  break;

        writeFile << (byte) symbol; 
	written++;
    }
    cerr << "done." << endl; 

    // Get actual size
    writeFile.seekp(0, ios_base::end);
    int outFile_end = writeFile.tellp();
    writeFile.seekp(0, ios_base::beg);
    int outFile_beg = writeFile.tellp();
    int outFile_size = outFile_end - outFile_beg; 

    // Compression ratio
    double uncompression_ratio = (double)outFile_size/inFile_size; 
    cerr << "Uncompression ratio: " << uncompression_ratio << endl; 

    // Close both files. 
    readFile.close(); 
    writeFile.close(); 

    return 0; 
}
