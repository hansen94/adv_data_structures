/*
 * Huffman Coding - PA 2 CSE 100
 *   by Aidan Macdonald <amacdona@ucsd.edu>
 *      Andrew Tsun <atsun@ucsd.edu>
 * 
 * 
 * 
 */

#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include "Tester.hpp"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>

#define READ_BYTE 2
#define READ_INT 1
#define READ_BIT 0

#define WRITE_BYTE 5
#define WRITE_INT 4
#define WRITE_BIT 3

#define BISBOS_TESTFILE "BitInputStream_input.txt"

using namespace std; 

int main(){
    
    /*** TESTING OF BIT OUTPUT STREAM ***/
    cout << "*** TESTING BIT OUTPUT STREAM ***" << endl << endl;
    
    // Prepare test file for writing. 
    cout << "Preparing \"" << BISBOS_TESTFILE << "\" for writing... ";
    ofstream writeFile("BitInputStream_input.txt");
    if(!writeFile){
        cerr << "Cannot write to test file. Test aborted." << endl;
        return 1; 
    }
    BitOutputStream bos(writeFile); 
    cout << "[DONE]" << endl; 
    
    // Lambda used to test writing. 
    auto testWrite = [&bos](int option, int input_val){
        switch(option){ 
            case WRITE_BYTE: bos.writeByte(input_val); break; 
            case WRITE_INT: bos.writeInt(input_val); break;
            default: bos.writeBit(input_val); break; 
        }
        if (option == WRITE_BYTE || option == WRITE_INT)
           cout << hex << input_val << "//";
        //else
            //cout << input_val;*/
    };

    // Write "a1b2c3", alternating from byte to int.
    cout << "Testing write of \"a1b2c3\"... 0x" << endl; 
    testWrite(WRITE_BYTE, 'a'); 
    testWrite(WRITE_INT, 1);
    testWrite(WRITE_BYTE, 'b'); 
    testWrite(WRITE_INT, 2);
    testWrite(WRITE_BYTE, 'c'); 
    testWrite(WRITE_INT, 3);
    cout << " [DONE]" << endl; 
    
    // Write out 'A'
    cout << "Testing bit-by-bit write of 'A': " << endl; 
    testWrite(WRITE_BIT, 0);
    testWrite(WRITE_BIT, 1);
    testWrite(WRITE_BIT, 0);
    testWrite(WRITE_BIT, 0);
    testWrite(WRITE_BIT, 0);
    testWrite(WRITE_BIT, 0);
    testWrite(WRITE_BIT, 0); 
    testWrite(WRITE_BIT, 1);
    cout << " [DONE]" << endl; 

    // Write out 'B'
    cout << "Testing bit-by-bit write of 'B': " << endl; 
    testWrite(WRITE_BIT, 0);
    testWrite(WRITE_BIT, 1);
    testWrite(WRITE_BIT, 0);
    testWrite(WRITE_BIT, 0);
    testWrite(WRITE_BIT, 0);
    testWrite(WRITE_BIT, 0);
    testWrite(WRITE_BIT, 1); 
    testWrite(WRITE_BIT, 0);
    cout << " [DONE]" << endl; 

    // Write out 'C'
    cout << "Testing bit-by-bit write of 'C': " << endl; 
    testWrite(WRITE_BIT, 0);
    testWrite(WRITE_BIT, 1);
    testWrite(WRITE_BIT, 0);
    testWrite(WRITE_BIT, 0);
    testWrite(WRITE_BIT, 0);
    testWrite(WRITE_BIT, 0);
    testWrite(WRITE_BIT, 1); 
    testWrite(WRITE_BIT, 1);
    cout << " [DONE]" << endl; 

    // Close output stream
    cout << "Closing BitOutputStream... ";
    writeFile.close(); 
    cout << "[DONE]" << endl << endl;

    /*** TESTING OF BIT INPUT STREAM ****/
    cout << "*** TESTING BIT INPUT STREAM ***" << endl << endl;
    // Prepare outputted file for reading. 
    cout << "Preparing \"" << BISBOS_TESTFILE << "\" for reading... "; 
    ifstream readFile("BitInputStream_input.txt");
    if(!readFile){
        cerr << "Cannot read test file. Test aborted." << endl;
        return 1; 
    }
    BitInputStream bis(readFile); 
    cout << "[DONE]" << endl; 

    // Lambda used to test reading. 
    auto testRead = [&bis](int option, int expected_val, string err_msg){
        int actual_val; 
        switch(option){ 
            case READ_BYTE: actual_val = bis.readByte(); break; 
            case READ_INT: actual_val = bis.readInt(); break;
            default: actual_val = bis.readBit(); break; 
        }
        //Tester::assert(actual_val == expected_val, err_msg);
        if (option == READ_BYTE || option == READ_INT)
            cout << hex << actual_val << "//"; 
        //else
            //cout << actual_val;*/
    };

    // Test reading of "a1b2c3"
    cout << "Testing read of \"a1b2c3\"... 0x" << endl;
    testRead(READ_BYTE, 'a', string("Byte != a")); 
    testRead(READ_INT, 1, string("Int != 1"));
    testRead(READ_BYTE, 'b', string("Byte != b")); 
    testRead(READ_INT, 2, string("Int != 2"));
    testRead(READ_BYTE, 'c', string("Byte != c")); 
    testRead(READ_INT, 3, string("Int != 3"));
    cout << " [DONE]" << endl; 

    // Read 'A'
    cout << "Testing bit-by-bit Read of 'A': " << endl; 
    testRead(READ_BIT, 0, string("Bit != 0"));
    testRead(READ_BIT, 1, string("Bit != 1"));
    testRead(READ_BIT, 0, string("Bit != 0"));
    testRead(READ_BIT, 0, string("Bit != 0"));
    testRead(READ_BIT, 0, string("Bit != 0"));
    testRead(READ_BIT, 0, string("Bit != 0"));
    testRead(READ_BIT, 0, string("Bit != 0")); 
    testRead(READ_BIT, 1, string("Bit != 1"));
    cout << " [DONE]" << endl; 

    // Read 'B'
    cout << "Testing bit-by-bit Read of 'B': " << endl; 
    testRead(READ_BIT, 0, string("Bit != 0"));
    testRead(READ_BIT, 1, string("Bit != 1"));
    testRead(READ_BIT, 0, string("Bit != 0"));
    testRead(READ_BIT, 0, string("Bit != 0"));
    testRead(READ_BIT, 0, string("Bit != 0"));
    testRead(READ_BIT, 0, string("Bit != 0"));
    testRead(READ_BIT, 1, string("Bit != 1")); 
    testRead(READ_BIT, 0, string("Bit != 0"));
    cout << " [DONE]" << endl; 

    // Read 'C'
    cout << "Testing bit-by-bit Read of 'C': " << endl; 
    testRead(READ_BIT, 0, string("Bit != 0"));
    testRead(READ_BIT, 1, string("Bit != 1"));
    testRead(READ_BIT, 0, string("Bit != 0"));
    testRead(READ_BIT, 0, string("Bit != 0"));
    testRead(READ_BIT, 0, string("Bit != 0"));
    testRead(READ_BIT, 0, string("Bit != 0"));
    testRead(READ_BIT, 1, string("Bit != 1")); 
    testRead(READ_BIT, 1, string("Bit != 1"));
    cout << " [DONE]" << endl;  

    // EOF testing
    cout << "Testing EOF detection of BitInputStream... "; 
    testRead(READ_BYTE, -1, string("readByte() did not detect EOF correctly.")); 
    testRead(READ_INT, -1, string("readInt() did not detect EOF correctly.")); 
    testRead(READ_BIT,-1, string("readBit() did not detect EOF correctly.")); 
    cout << "[DONE]" << endl; 
    // Close input stream
    cout << "Closing \"" << BISBOS_TESTFILE << "\"... ";
    readFile.close(); 
    cout << "[DONE]" << endl; 
    return 0; 
}
