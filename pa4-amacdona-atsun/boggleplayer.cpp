/** Boggle Player
 * Authors: Aidan Macdonald, Andrew Tsun
 * 
 * Filename: boggleplayer.cpp 
 * Description: This file provides implementations for a boggle player. 
 * 
 */


#include "boggleplayer.h"
#include <vector>
#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <assert.h>
#include <stack>
#include <string>

// Initialize BogglePlayer without buildLexicon nor setBoard called. 
BogglePlayer::BogglePlayer(): buildLexiconCalled(false), 
                              setBoardCalled(false) {} 

/*
  buildLexicon: takes as argument a set containing the words specifying 
  the official lexicon to be used for the game. Each word in the set will 
  be a string consisting of lowercase letters a-z only. This function must 
  load the words into an efficient data structure (a multiway trie) that 
  will be used internally as needed by the BogglePlayer. The multiway trie 
  maintains the BogglePlayer's lexicon. For a good-objected oriented design 
  the multiway trie should be implemented in a different class 
  (possibly in the file boggleutil.h/cpp) and appropriately used by the 
  BogglePlayer class.
*/
void BogglePlayer::buildLexicon(const set<string>& word_list) {
  for (set<string>::iterator si = word_list.begin();
       si != word_list.end();
       si++)
    this->bl.addWord(*si);
  buildLexiconCalled = true; 
}


void BogglePlayer::doTouch(const std::vector<int> & bv) {
  for (std::vector<int>::const_iterator itr = bv.begin();
       itr != bv.end();
       itr++) {
    size_t col = *itr % this->board.size();
    size_t row = (*itr - col)/this->board.size();
    this->board[row][col].touched = true;
  }
}

void BogglePlayer::clearTouch() {
  for (size_t r = 0;r<this->board.size();r++)
    for (size_t c = 0;c<this->board[r].size();c++)
      this->board[r][c].touched = false;
}

bcharvector BogglePlayer::getNeighbors(int row, int col, bool untouched,
				    const std::unordered_set<int> & exclude){
  bcharvector n;
  // Iterate on a 3x3 matrix surrounding the current point. 
  for (int r = row-1;r<=row+1;r++) {
    for (int c = col-1;c<=col+1;c++) {
      if ( (r >= 0 && r < (int)this->board.size()) && // check row is valid
	   (c >= 0 && c < (int)this->board[0].size()) && // check col is valid
	   !(r == row && c == col) &&
	   (!this->board[r][c].touched || !untouched) &&
	   exclude.find(r*this->board.size() + c) == exclude.end() ) {
	n.push_back(this->board[r][c]);
      }
    }
  }

  return n;
}

/*
  setBoard: takes two arguments: the number of rows and columns in the board, 
  and an array of arrays of strings representing what is shown on the face 
  of dice on a Boggle board. A Boggle board is a rectangular grid of dice; 
  the height (number of rows) is given by the first argument, the width of 
  this grid (i.e. number of columns) is given by the second argument. The 
  elements of the vector specify the contents of the board in row major order. 
  That is, consider the board as a two-dimensional array, with columns 
  indexed 0 to width, and rows indexed 0 to height. The die at row R and 
  column C has on its face the string in the position diceArray[R][C]. Each 
  string may be upper or lower case, and may contain one or more letters. 
  (In official Boggle, these strings would contain one character only, 
  except for the double letter die face "Qu"; but your BogglePlayer should 
  work correctly for strings of any length as we have modified the game so 
  that a die can show multi-character strings, e.g. "ion") For purposes of 
  finding words on the board, they should all be considered lowercase. 
  Therefore, this function should convert the strings on each die face to 
  lower case. The function will then use the transformed information to 
  construct a data structure representing the Boggle board in a way that
  lends itself well to your search algorithms.
*/
void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, 
                            string** diceArray) {
  this->board.resize(rows, bcharvector(cols));
  for (size_t r=0;r<rows;r++) {
    this->board[r].resize(cols);
    for (size_t c=0;c<cols;c++)
      this->board[r][c] = bchar(diceArray[r][c], r, c, false);
  }
  setBoardCalled = true; 
}


void BogglePlayer::getLocalWord(size_t row, size_t col,
				size_t minLen,
				BoggleLexicon *bl,
				std::unordered_set<int> exclude,
				std::string str,
				std::set<string> *words) {
  if (bl == NULL)
    return;

  if (bl->endsWord && str.size() >= minLen) {
    words->insert(str);
  }

  BoggleLexicon *next = bl;
  std::string here = this->board[row][col].c;

  for (size_t i=0;i<here.size() && next != NULL;i++) {
    if (next->children.find(here[i]) != next->children.end()) {
      next = next->children[here[i]];
    } else {
      return;
    }
  }

  if (next == NULL)
    return;

  exclude.insert(row*this->board.size() + col);  
  for (bchar b : this->getNeighbors(row, col, true, exclude)) {
    std::string tmp = str;
    this->getLocalWord(b.row, b.col, minLen, next, 
                       exclude, tmp.append(here), words);
  }
}


/*
  getAllValidWords: takes two arguments: an int specifying a minimum word 
  length, and a pointer to a set of strings. It returns false if either 
  setBoard() or buildLexicon() have not yet been called for this BogglePlayer.
  If they have both been called, it will return true, after filling the set 
  with all the words that (1) are of at least the given minimum length, 
  (2) are in the lexicon specified by the most recent call to buildLexicon(),
  and (3) can be found by following an acyclic simple path
  on the board specified by the most recent call to setBoard().
*/
bool BogglePlayer::getAllValidWords(unsigned int minLen, set<string>* words) {
  if (buildLexiconCalled == false || setBoardCalled == false)
    return false;

  for (size_t r = 0;r < this->board.size();r++) {
    for (size_t c = 0;c < this->board[r].size();c++) {
      this->getLocalWord(r, c, minLen, &this->bl, 
        std::unordered_set<int>(), "", words);
    }
  }

  return true;
}

bool BogglePlayer::isInLexicon(const string& word_to_check) {
  return bl.checkWord(word_to_check);
}


/*
  isOnBoard: takes as argument a string passed by reference. It determines 
  whether the string can be found by following an acyclic simple path on the 
  board specified by the most recent call to setBoard(). If it is possible to
  find the word in the current board, the function returns a vector with 
  integers specifying the locations of dice that can be used to form the word, 
  in the order that spells the word. The integers used to specify the 
  locations shall be in row-major-order indices. That is, if a letter is in 
  row R and column C, the location will be R*Width+C. If it is NOT possible 
  to form the word, or if setBoard() has not yet been called, the function 
  returns an empty vector.
*/
std::vector<int> BogglePlayer::isOnBoard(const string& word) {
  std::stack<bchar*> bstack;
  std::vector<int> path;                                          
  std::string word_to_check = word; 
  std::transform(word_to_check.begin(), word_to_check.end(), 
                 word_to_check.begin(), ::tolower);

  for (size_t r = 0;r < this->board.size();r++) {
    for (size_t c = 0; c < this->board[r].size(); c++) {
      board[r][c].touched = false;
      bstack.push(&board[r][c]);
    }
  }
  
  size_t pos = 0; // Index in string
  assert(pos < word_to_check.size() && bstack.size() > 0);
  while (pos < word_to_check.size() && bstack.size() > 0) {
    bchar* b = bstack.top();
    bstack.pop();

    if (b == NULL) {
      assert(path.size() > 0);
      
      // Untouch last path element
      size_t c = path.back() % this->board.size();
      size_t r = (path.back() - c)/this->board.size();
      assert(r < this->board.size());
      assert(c < this->board[r].size()); 
      this->board[r][c].touched = false;

      // Decrement string index
      assert(pos >= this->board[r][c].c.size());
      pos -= this->board[r][c].c.size();
      path.pop_back();
    } else if ( !b->touched && 
		word_to_check.substr(pos, b->c.size()) == b->c ) {
      // Increment string index
      pos += b->c.size();
      assert(pos <= word_to_check.size());

      // Push level marker
      bstack.push(NULL);
      
      // Add path element
      assert(this->board.size() > 0);
      path.push_back(b->row * this->board[0].size() + b->col);
      
      // Add all neighbors
      for (bchar nb : this->getNeighbors(b->row, b->col))
	bstack.push(&this->board[nb.row][nb.col]);

      b->touched = true;
      assert(b->touched == true);
    }
  }

  assert(pos <= word_to_check.size());

  this->clearTouch();
  if (pos == word_to_check.size()) {
    return path;
  } else {
    return std::vector<int>();
  }
}

size_t BogglePlayer::expectedPathLen(std::string word) {
  size_t total = 0;

  for (size_t r = 0;r < this->board.size();r++) {
    for (size_t c = 0;c < this->board[r].size();c++) {
      bchar cur = this->board[r][c];
      size_t i;

      while ((i = word.find(cur.c)) != std::string::npos) {
	word.erase(i, cur.c.size());
	total++;
      }
    }
  }

  return total;
}

void BogglePlayer::getCustomBoard(string** &board, unsigned int *rows, 
                                  unsigned int *cols) {

    // Set rows and columns
    *rows = 4;
    *cols = 4;
    unsigned int r = *rows;
    unsigned int c = *cols; 
 
    // Allocate board
    board = new string*[r];
    for (size_t i=0;i<r;i++)
      board[i] = new string[c];
   
    // Initialize values here
    board[0][0] = "s";
    board[0][1] = "t";
    board[0][2] = "h";
    board[0][3] = "r";

    board[1][0] = "qu";
    board[1][1] = "a";
    board[1][2] = "v";
    board[1][3] = "i";

    board[2][0] = "a";
    board[2][1] = "t";
    board[2][2] = "d";
    board[2][3] = "j";

    board[3][0] = "u";
    board[3][1] = "l";
    board[3][2] = "t";
    board[3][3] = "r";

    setBoard(r, c, board);
}


