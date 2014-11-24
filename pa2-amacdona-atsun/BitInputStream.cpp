/*
 * Huffman Coding - PA 2 CSE 100
 *   by Aidan Macdonald <amacdona@ucsd.edu>
 *      Andrew Tsun <atsun@ucsd.edu>
 * 
 * Bit IO Implementation
 * 
 */

#include "BitInputStream.hpp"


/** Read the next bit from the bit buffer included.
 *  If the bit buffer is currently empty,
 *  fill the bit buffer by reading a char from the istream first.
 *  Return the bit read as the least signficant bit of an int.
 *  Return -1 on EOF.
 *  This must be consistent with BitOutputStream::writeBit(), in terms
 *  of ordering of bits in the stream.
 */
int BitInputStream::readBit() {
    if ( bufi == ((int)(sizeof(char)*8)) ){
      int b = this->readByte();
      if (b == EOF_REACHED)
	       return -1;
      this->buf = (char)(b & 0xFF);
      bufi = 0;
    }
    // Read from buffer.
    int ret = ((this->buf & 0x01) == 1 ? 1 : 0);
    bufi++;
    this->buf = this->buf >> 1; // Drop a bit

    return ret;
}

/** Read a byte from the ostream.
 *  Return -1 on EOF.
 *  This function doesn't touch the bit buffer.
 *  The client has to manage interaction between reading bits
 *  and reading bytes.
 */
int BitInputStream::readByte() {
    // Return -1 on EOF
    if (in.eof())
        return EOF_REACHED;
    // Read in a byte
    unsigned char ret_val = 0; 
    in.read((char*)&ret_val, sizeof(ret_val));
    // Cast return value to int 
    return (int) ret_val; 
}

/** Read a non-negative int from the ostream.
 *  Return -1 on EOF.
 *  This function doesn't touch the bit buffer.
 *  The client has to manage interaction between reading bits
 *  and reading ints.
 */
int BitInputStream::readInt() {
    // Return -1 on EOF
    if (in.eof())
        return EOF_REACHED;

    int ret_val = 0; 
    in.read((char*)&ret_val, sizeof(ret_val));
    // Cast return value to int 
    return (int) ret_val; 
}

