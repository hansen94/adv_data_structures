/** Boggle Utilities
 *  Authors: Aidan Macdonald, Andrew Tsun
 *
 *  Filename: boggleutil.cpp
 *  Description: Provides implementations for auxiliary functions used by
 *  BogglePlayer. 
 */
#include <iostream>
#include "boggleutil.h"
#include <locale>
#include <string>

/**
 * Creates a data structure that holds information on a given 
 * position on the boggle board. Short for "board character"
 */
bchar::bchar(std::string c, size_t row, size_t col, bool touched) {
  this->c = c;
  std::locale loc;
  for (std::string::size_type i=0; i<this->c.length();i++)
    this->c[i] = std::tolower(this->c[i], loc);

  this->row = row;
  this->col = col;
  this->touched = touched;
}

/*
 Copy constructor for bchar.
 */
bchar::bchar(const bchar & bc) {
  this->c = bc.c;
  this->row = bc.row;
  this->col = bc.col;
  this->touched = bc.touched;
}

/*
 Assignment operator for bchar
 */
bchar& bchar::operator= (const bchar & bc) {
  this->c = bc.c;
  this->row = bc.row;
  this->col = bc.col;
  this->touched = bc.touched;

  return *this;
}

/*
 Compares the first character of a string in a bchar to a character.
 Returns true if they are the same, false otherwise.
 */ 
bool bchar::operator== (const char & c) {
  return this->c[0] == c;
}

/*
 Compares the string of the bchar to another string.
 Returns true if they are the same, false otherwise. 
 */ 
bool bchar::operator== (const std::string & c) {
  return this->c == c;
}

/*
 Compares a bchar to another bchar.
 Returns true if their position and stored string are the same.  
 */
bool bchar::operator== (const bchar & b) {
  return this->c == b.c && this->row == b.row && this->col == b.col;
}

/*
 Serializes a bchar to an ostream. 
 */
std::ostream& operator<< (std::ostream& os, const bchar & b) {
  return os << "[" << b.c << " @ (" 
	    << b.row << "," << b.col << ") " 
	    << (b.touched ? "T" : "UT") << " ]";
}

/*
 Serializes a vector containing bchar's to an ostream. 
 */
std::ostream& operator<< (std::ostream& os, const bcharvector & bv) {
  os << "{ ";
  for (bcharvector::const_iterator bi = bv.begin();
       bi != bv.end();
       bi++)
    os << " " << *bi << " ";
  os << " }";
  return os;
}

/*
 Creates the lexicon used by the Boggle board. 
 */ 
BoggleLexicon::BoggleLexicon() {
  this->endsWord = false;
}

/*
  Destroys the lexicon used by the Boggle board. 
 */
BoggleLexicon::~BoggleLexicon() {
  for (blcharmap::iterator itr = this->children.begin();
       itr != this->children.end();
       itr++)
    if (itr->second != NULL)
      delete itr->second;
}

/*
 * addWord: adds a word to the lexicon
 */

void BoggleLexicon::addWord(const std::string & bv) {
  if (bv.size() <= 0) {
    this->endsWord = true;
    return;
  }

  std::locale loc;
  char lower = std::tolower(bv[0], loc);
  
  if (this->children[lower] == NULL)
    this->children[lower] = new BoggleLexicon();
  
  this->children[lower]->addWord(bv.substr(1, bv.size()));
}

/*
  checkWord: checks to see if a word exists in the lexicon
 */ 
bool BoggleLexicon::checkWord(const std::string & bv) {
  if (bv.size() <= 0) {
    return this->endsWord;
  }

  std::locale loc;
  char lower = std::tolower(bv[0], loc);
  
  if (this->children.find(lower) == this->children.end())
    return false;
  
  return this->children[lower]->checkWord(bv.substr(1, bv.size()));
}

/*
 A way to serialize a lexicon to an ostream. 
 */ 
std::ostream& operator<< (std::ostream &os, const BoggleLexicon &bl) {
  os << "{ " << (bl.endsWord ? "END" : "NOT") << " | ";
  for (std::pair<char, BoggleLexicon*> p : bl.children) {
    if (p.second != NULL)
      os << " " << p.first << ":" << *p.second << " ";
  }
  os << " }";
  return os;
}

