/*
 * Huffman Coding - PA 2 CSE 100
 *   by Aidan Macdonald <amacdona@ucsd.edu>
 *      Andrew Tsun <atsun@ucsd.edu>
 * 
 * 
 * 
 */

#ifndef TESTER
#define TESTER

#define DONE "[DONE]."

#include <sstream>
#include <iostream>
#include <string> 

#define EXEC(cmd) \
  std::cout << "Running: " << #cmd << std::endl; \
  cmd;

using namespace std;

namespace Tester {
    bool assert(bool condition, stringstream& err_msg);
    bool assert(bool condition, const string& err_msg); 
};


#endif 
