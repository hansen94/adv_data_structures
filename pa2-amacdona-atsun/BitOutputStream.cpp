/*
 * Huffman Coding - PA 2 CSE 100
 *   by Aidan Macdonald <amacdona@ucsd.edu>
 *      Andrew Tsun <atsun@ucsd.edu>
 * 
 * Bit IO Implementation
 * 
 */

#include "BitOutputStream.hpp"

/** Write the least significant bit of the argument into
 *  the bit buffer, and increment the bit buffer index.
 *  Flush to the ostream first if the bit buffer is full.
 *  This must be consistent with BitInputStream::readBit().
 */

void BitOutputStream::writeBit(int bit) {
     // If buffer is full, flush it.
    if (bufi == (int)sizeof(char)*8)
        flush();
    // Write to buffer.

#define HIGH_BIT (0x01 << ((int)(sizeof(char)*8-1)))
    buf = (bit == 1 ? 
	   buf >> 1 | HIGH_BIT : // Set High Bit on
	   buf >> 1 & ~HIGH_BIT); // Set High Bit off
#undef HIGH_BIT

    // 1 more bit has been added.
    bufi++;
    //cout << "bufi = " << bufi << endl; 
}

/** Write the least significant byte of the argument to the ostream.
 *  This function doesn't touch the bit buffer.
 *  The client has to manage interaction between writing bits
 *  and writing bytes.
 */

void BitOutputStream::writeByte(int b) {
  char c = b;
  this->out.write((char*)&c, sizeof(c));
}

/** Write the argument to the ostream.
 *  This function doesn't touch the bit buffer.
 *  The client has to manage interaction between writing bits
 *  and writing ints.
 */

void BitOutputStream::writeInt(int i) {
  this->out.write((char*)&i, sizeof(i));
}

/** If the bit buffer contains any bits, flush the bit buffer to the ostream,
 *  clear the bit buffer, and set the bit buffer index to 0.
 *  Also flush the ostream itself.
 */

void BitOutputStream::flush() {
  // Shift so that the first bit ever written is right most
  // in case of part full buffer
  // Satisfies necessary condition that nothing happens
  // for bufi == 8.
  this->buf = this->buf >> (((int)(sizeof(char)*8))-this->bufi);

  this->writeByte(this->buf);
  buf = 0; 
  bufi = 0;
}
