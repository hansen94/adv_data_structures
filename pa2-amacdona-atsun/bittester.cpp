/*
 * Huffman Coding - PA 2 CSE 100
 *   by Aidan Macdonald <amacdona@ucsd.edu>
 *      Andrew Tsun <atsun@ucsd.edu>
 * 
 * 
 * 
 */

#include <iostream>
#include <fstream>
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include <stdlib.h>
#include <time.h>

#define MSGSIZE 1000000

#define EXEC(cmd) \
  std::cout << "EXEC: " << #cmd << std::endl;	\
  cmd;

int main() {
  char bytemsg[MSGSIZE];
  int  intmsg[MSGSIZE];
  char binmsg[MSGSIZE];
  
  // Randomly generate a bunch of bytes
  srand(time(NULL));
  for (size_t i=0;i<MSGSIZE;i++) {
    bytemsg[i] = rand();
    intmsg[i]  = rand();
    binmsg[i]  = rand();
  }

#define BW (std::fstream::binary | std::fstream::out)
  std::fstream byteof ("/tmp/tmpByte001", BW);
  std::fstream intof  ("/tmp/tmpInt001", BW);
  std::fstream binof  ("/tmp/tmpBin001", BW);
  
  BitOutputStream bobyte = BitOutputStream(byteof);
  BitOutputStream boint = BitOutputStream(intof);
  BitOutputStream bobin = BitOutputStream(binof);

  for (size_t i=0;i<MSGSIZE;i++) {
    bobyte.writeByte(bytemsg[i]);
    boint.writeInt(intmsg[i]);

    char bin = binmsg[i];
    for (size_t j=0;j<sizeof(char);j++) {
      bobin.writeBit(bin & 0x01);
      bin = bin >> 1;
    }
  }

  bobyte.flush();
  byteof.close();

  boint.flush();
  intof.close();

  bobin.flush();
  binof.close();

#define BR (std::fstream::binary | std::fstream::in)
  std::fstream byteif ("/tmp/tmpByte001", BR);
  std::fstream intif  ("/tmp/tmpInt001",  BR);
  std::fstream binif  ("/tmp/tmpBin001",  BR);
  
  BitInputStream bibyte = BitInputStream(byteif);
  BitInputStream biint = BitInputStream(intif);
  BitInputStream bibin = BitInputStream(binif);
  

  double interr, byterr, binerr;
  interr = byterr = binerr = 0;
  for (size_t i=0;i<MSGSIZE;i++) {
    if ( ((char)bibyte.readByte()) != bytemsg[i] )
      byterr++;

    if ( biint.readInt() != intmsg[i] )
      interr++;

    char bin = binmsg[i];
    for (size_t j=0;j<sizeof(char);j++) {
      if ( bibin.readBit() != (int)(bin & 0x01) )
	binerr++;
      bin = bin >> 1;
    }
  }

  std::cout << "Byte Error: " << byterr/MSGSIZE << "%" << std::endl;
  std::cout << "Int  Error: " << interr/MSGSIZE << "%" << std::endl;
  std::cout << "Bin  Error: " << binerr/MSGSIZE << "%" << std::endl;

  return 0;
}
