/** Boggle Player
 *  Authors: Aidan Macdonald, Andrew Tsun
 * 
 *  Filename: boggleplayer.h
 *  Description: method signatures for an AI Boggle player
 */


#ifndef BOGGLE_PLAYER
#define BOGGLE_PLAYER

#include "baseboggleplayer.h"
#include <vector>
#include "boggleutil.h"
#include <unordered_set>


class BogglePlayer: public BaseBogglePlayer {
 private:
  // Defined board[ROW][COL]
  bool buildLexiconCalled;
  bool setBoardCalled;
  BoggleLexicon bl;
  bcharmatrix board;
  bchar toBChar(char c, size_t row, size_t col, bool touched);

  // Get About integers for negativity reasons
  bcharvector getNeighbors(int row, int col, bool untouched=true,
	    const std::unordered_set<int>& exclude=std::unordered_set<int>());
  void clearTouch();
  void doTouch(const std::vector<int> & bv);
  void getLocalWord(size_t row, size_t col,
		    size_t minLen,
		    BoggleLexicon *bl,
		    std::unordered_set<int> exclude,
		    std::string str,
		    std::set<string> *words);
  std::vector<int> wordPath(size_t row, size_t col, std::string word, 
                            std::vector<int> path);

  size_t expectedPathLen(std::string word);

 public:
  BogglePlayer(); 
  void buildLexicon(const set<string>& word_list);
  void setBoard(unsigned int rows, unsigned int cols, string** diceArray);
  bool getAllValidWords(unsigned int minimum_word_length, set<string>* words);
  bool isInLexicon(const string& word_to_check);
  std::vector<int> isOnBoard(const string& word_to_check);
  void getCustomBoard(string** &new_board, unsigned int *rows, 
                      unsigned int *cols);
};

#endif
