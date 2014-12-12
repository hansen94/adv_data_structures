/** Boggle Utilites
 * Authors: Aidan Macdonald, Andrew Tsun
 * 
 * Filename: boggleutil.h
 * Description: Method signatures for auxilary classes/methods for 
 *              BogglePlayer. 
 */

#ifndef BOGGLE_UTIL
#define BOGGLE_UTIL

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

class bchar {
 public:
  std::string c;
  size_t row;
  size_t col;
  bool touched;

  bchar(std::string c="", size_t row=0, size_t col=0, bool touched=false);
  bchar(const bchar & bc);
  bchar& operator= (const bchar & bc);
  
  bool operator== (const bchar & bc);
  bool operator== (const std::string & c);
  bool operator== (const char & c);
};

typedef std::vector<bchar> bcharvector;
typedef std::vector<bcharvector> bcharmatrix;

std::ostream& operator<< (std::ostream& os, const bcharvector & bv);
std::ostream& operator<< (std::ostream& os, const bchar & b);

class BoggleLexicon;

typedef std::unordered_map<char, BoggleLexicon*> blcharmap;

class BoggleLexicon {
public:
  blcharmap children;
  bool endsWord; // Does this Lexicon Node end a word?

  BoggleLexicon();
  ~BoggleLexicon();
  
  void addWord(const std::string & bv);
  bool checkWord(const std::string & bv);
};

std::ostream& operator<< (std::ostream &os, const BoggleLexicon &bl);

#endif
