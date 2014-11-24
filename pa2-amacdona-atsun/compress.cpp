/*
 * Huffman Coding - PA 2 CSE 100
 *   by Aidan Macdonald <amacdona@ucsd.edu>
 *      Andrew Tsun <atsun@ucsd.edu>
 * 
 * Main file for compress
 * 
 */

#include "HCTree.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <utility> 
#include <algorithm>
#include <iterator>
#include <ios> 
#include <string>

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
    ifstream readFile(argv[1]); 
    if (!readFile){  
        //cerr << "Error opening \"" << argv[1] << "\". " << endl;
        cerr << "Error opening \"0\"." << endl; 
        return 3; 
    }
    
    // Open up output file for writing, check for successful open. 
    ofstream writeFile(argv[2], ios::binary);    
    if (!writeFile){
        //cerr << "Error opening \"" << argv[2] << "\"." << endl;
        cerr << "Error opening \"0\"." << endl; 
        return 4; 
    } 

    // Generate frequency vector 
    cerr << "Reading from file \"" << argv[1] << "\"... ";
    vector<int> frq(256, 0);
    int unique = 0; // Count number of unique characters
    while ( ((int)readFile.peek()) != EOF ){
        byte b = readFile.get();
        if(frq[(int)b] == 0) // Note unique characters.
            unique++; 
        frq[(int)b]++; 
    }

    // Input file size
    cerr << "done." << endl;
    readFile.seekg(0, ios_base::end);
    int inFile_end = readFile.tellg();
    readFile.seekg(0, ios_base::beg); 
    int inFile_beg = readFile.tellg();
    int inFile_size = inFile_end - inFile_beg; 

    cerr << "Found " << unique << " unique symbols in input file of "; 
    cerr << "size " << inFile_size << " bytes." << endl; 
    
    // Build Huffman tree
    cerr << "Building Huffman code tree... ";
    HCTree tree;
    tree.build(frq); 
    cerr << "done." << endl; 
    
    // Begin writing to the header, start with file size
    cerr << "Writing to file \"" << argv[2] << "\"... ";
    BitOutputStream bos (writeFile);
    bos.writeInt(inFile_size);
    
    // Write the frequency vector to the header
    bos.writeInt(unique); 
    for(unsigned int i = 0; i < frq.size(); i++){
      if (frq[i] != 0) {
        bos.writeByte(i); 
        bos.writeInt(frq[i]); 
      }
    }

    // Encode to the tree. 
    
    while( ((int)readFile.peek()) != EOF ) {
        byte b = readFile.get();
        tree.encode(b, bos); 
    }
    bos.flush();
    writeFile.flush();
    cerr << "done." << endl; 

    // Output file size
    writeFile.seekp(0, ios_base::end);
    int outFile_end = writeFile.tellp();
    writeFile.seekp(0, ios_base::beg);
    int outFile_beg = writeFile.tellp();
    int outFile_size = outFile_end - outFile_beg;
    cerr << "Output file has size " << outFile_size << " bytes." << endl;

    // Compression Ratio
    double compression_ratio = (double)outFile_size/inFile_size; 
    cerr << "Compression ratio: " << compression_ratio << endl; 

    // Close both files. 
    readFile.close(); 
    writeFile.close(); 
                             
    return 0; 
}
