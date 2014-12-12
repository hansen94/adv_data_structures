/******************************************************
 * Tester file to test basic functionality of your code
 * ****************************************************/

#include "baseboggleplayer.h"
#include "boggleplayer.h"
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <iostream>
#include <utility>
#include "boggleutil.h"
#include <set>
#include <ctime>
#include <fstream>
#include <assert.h>
#include <cstdio>

using namespace std;

int ryan_test(); 

class BoggleTester{

public:

  void testLexicon(){
    cout << "*** TESTING LEXICON ( buildLexicon() and isinLexicon() ) ***" << endl; 
    // Build lexicon
    cout << "Initializing lexicon..." << endl; 
    BogglePlayer bp;  
    string word1 = "this";
    string word2 = "that";
    string word3 = "whatever";
    set<string> wl; 
    auto insert = [&wl](string word){
       cout << "Inserting \"" << word << "\"... ";
       wl.insert(word);
       cout << "[DONE]" << endl; 
    };

    insert(word1); 
    insert(word2); 
    insert(word3);

    cout << "Building lexicon... "; 
    bp.buildLexicon(wl); 
    cout << "[DONE]" << endl; 

    auto checkWordTest = [&bp](string word, bool expected){
      cout << "Checking lexicon for \"" << word << "\"... ";
      if(bp.isInLexicon(word) && expected)
        cout << "[FOUND]" << endl; 
      else if(!bp.isInLexicon(word) && !expected)
        cout << "[NOT FOUND]" << endl;
      else if(bp.isInLexicon(word) && !expected)
        cout << "ERROR: \"" << word << "\" is not supposed to be in the lexicon" << endl;  
      else 
        cout << "ERROR: \"" << word << "\" is supposed to be in the lexicon" << endl;  
    };

    // Test words in lexicon. 
    checkWordTest(word1, true); 
    checkWordTest(word2, true);
    checkWordTest(word3, true); 

    // Test words not in lexicon.
    checkWordTest(string("thit"), false);
    checkWordTest(string("thas"), false); 
    checkWordTest(string("watever"), false); 
 
    cout << "Cleaning up test...";
    cout << "[DONE]" << endl << endl; 
  }


  void testChkpt(){
    BogglePlayer bp; 
    string **board;
    board = new string*[4];
    for (size_t i=0;i<4;i++)
      board[i] = new string[4];
  
    // Initialize board  
    cout << "*** TESTING CHECKPOINT ( isOnBoard() and setBoard() ) ***" << endl; 
    cout << "Initializing board..." << endl;
    cout << "    s  t h r   " << endl; 
    cout << "    qu a v i   " << endl;
    cout << "    a  t d j   " << endl; 
    cout << "    c  p n e  " << endl << endl;      
 
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

    board[3][0] = "c";
    board[3][1] = "p";
    board[3][2] = "n";
    board[3][3] = "e";

    bp.setBoard(4,4,board); 
	
    // Check for words.

    auto checkWord = [&bp](const string& word, bool should_be_found){
       cout << "Checking for word \"" << word << "\"... ";
       vector<int> path = bp.isOnBoard(word);
       // If vector comes up empty
       if(path.size() == 0){
         if(should_be_found == true)
           cerr << endl << "ERROR: \"" << word << "\" should be found on board." << endl;  
         else
           cout << "[NOT FOUND]" << endl;
       }
       // If vector does not come up empty. 
       else{
         if(should_be_found == false)
           cerr << endl << "ERROR: \"" << word << "\" should not be found on board." << endl;  
         else{
           cout << "[FOUND]" << endl; 
           cout << "Path to find \"" << word << "\" is: ";
           for(int coor: path){
	     cout << "(" << coor <<  ") ";
           }
           cout << endl; 
        }  
      }
    };

    // Words that exist
  
    checkWord("qua", true);
    checkWord("tsadi", true);
    checkWord("stat", true);
    checkWord("hadj", true);
    checkWord("asquat", true); 
    checkWord("aqua", true); 
 
    // Words that don't exist.
    checkWord("staqus", false);
    checkWord("tdnptat", false);
    checkWord("asdfghjkl", false);
    checkWord("pad", false);
    checkWord("vvvvvvvv", false);

    cout << "Cleaning up test...";
    for (size_t i=0;i<4;i++)
      delete[] board[i];
    delete[] board;
    cout << "[DONE]" << endl << endl; 
  }

  void testSpeed(){
    cout << "*** TESTING WORD RETRIEVAL ( getAllValidWords() ) ***" << endl;
    BogglePlayer bp; 
     
    // Initialize board 
    cout << "Initializing board... ";
    std::ifstream brd ("brd.txt");
    if(!brd){
      cerr << "brd.txt does not exist. Aborting test." << endl; 
      return; 
    }

    unsigned int rows, cols;
    brd >> rows;
    brd >> cols;
    std::string** sbrd = new std::string*[rows];
    for (unsigned int r=0;r<rows;r++) {
      sbrd[r] = new std::string[cols];
      for (unsigned int c=0;c<cols;c++) {
        brd >> sbrd[r][c];
      }
    }
    bp.setBoard(rows, cols, sbrd);
    brd.close();
    cout << "[DONE]" << endl; 
 
    // Initialize lexicon
    cout << "Initializing lexicon... ";
    std::set<std::string> word_list;
    std::ifstream dict ("lex.txt");
    if(!dict){
      cerr << "lex.txt does not exist. Aborting test." << endl; 
      return; 
    }
  
    while (!dict.eof()) {
      std::string tmp;
      dict >> tmp;
      word_list.insert(tmp);
    }
  
    bp.buildLexicon(word_list);
    dict.close();
    cout << "[DONE]" << endl;    

    // Time word retrieval 
    cout << "Timing word retrieval using getAllValidWords(): ";
    std::set<std::string> words_found;
    clock_t start = clock(); 
    bool result = bp.getAllValidWords(2, &words_found);
    clock_t end = clock(); 
    float runtime = (float)(end-start) / CLOCKS_PER_SEC;

    cout << "Found " << words_found.size() << "/5450 words in " << runtime << " seconds." << endl;
    cout << "Return value when setBoard() and buildLexicon() previously called is: " << (result ? "true" : "false") << endl; 

    cout << "getAllValidWords() return value when only buildLexicon() called: "; 
    BogglePlayer bp2; 
    bp2.buildLexicon(word_list);
    std::set<std::string> words_found2; 
    result = bp2.getAllValidWords(2, &words_found2);
    cout << (result ? "true" : "false") << endl; 

    cout << "getAllValidWords() return value when only setBoard() called: "; 
    BogglePlayer bp3; 
    bp3.setBoard(rows, cols, sbrd);
    std::set<std::string> words_found3; 
    result = bp3.getAllValidWords(2, &words_found3);
    cout << (result ? "true" : "false") << endl;

    cout << "getAllValidWords() return value when neither buildLexicon() nor setBoard() are called: "; 
    BogglePlayer bp4; 
    std::set<std::string> words_found4; 
    result = bp4.getAllValidWords(2, &words_found4);
    cout << (result ? "true" : "false") << endl; 

    cout << "getAllValidWords() return value when buildLexicon() called on nonempty lexicon, setBoard() called on empty board: "; 
    BogglePlayer bp5;  
    std::string** empty_brd = new std::string*[0];
    for (unsigned int r=0;r<0;r++) {
      empty_brd[r] = new std::string[0];
    } 
    bp5.setBoard(0,0,empty_brd);
    bp5.buildLexicon(word_list);
    std::set<std::string> words_found5;    
    result = bp5.getAllValidWords(2, &words_found5);
    cout << (result ? "true" : "false");  
    cout << ", Words found: " << words_found5.size() << endl;  

    cout << "getAllValidWords() return value when buildLexicon() called on empty lexicon, setBoard() called on nonempty board: "; 
    BogglePlayer bp6; 
    bp6.setBoard(rows, cols, sbrd);
    std::set<std::string> empty_wordlist;
    bp6.buildLexicon(empty_wordlist);
    std::set<std::string> words_found6;  
    result = bp6.getAllValidWords(2, &words_found6);
    cout << (result ? "true" : "false"); 
    cout << ", Words found: " << words_found6.size() << endl;  

    cout << "getAllValidWords() return value when buildLexicon() called on empty lexicon, setBoard() called on empty board: "; 
    BogglePlayer bp7; 
    bp6.setBoard(0,0,empty_brd);
    bp6.buildLexicon(empty_wordlist);
    std::set<std::string> words_found7;  
    result = bp6.getAllValidWords(2, &words_found7);
    cout << (result ? "true" : "false");  
    cout << ", Words found: " << words_found7.size() << endl;  

    cout << "Cleaning up test... ";
    for (unsigned int r=0;r<rows;r++)
      delete[] sbrd[r];
    delete[] sbrd;

    for(unsigned int r=0; r<0; r++)
      delete[] empty_brd[r];
    delete[] empty_brd; 

    cout << "[DONE]" << endl << endl; 
  }

};

int main(){
  BoggleTester bt;
  bt.testChkpt(); 
  bt.testLexicon();
  bt.testSpeed();  
  ryan_test(); 
}

/**
 * This test was provided by Ryan Bridges, located here: 
 * http://pastebin.com/gr1Ndyy7
 */ 
int ryan_test()
{
    cout << "*** Running comprehensive test as provided by Ryan Bridges ***" << endl;
    BogglePlayer* player = new BogglePlayer();

    set<string> validWords;
    string testString;
    set<string> lex;
    vector<int> positions;
    bool failed = false;

    string row0[] = {"A", "B", "C", "IN", "U"};
    string row1[] = {"M", "QEW", "NG", "J", "K"};
    string row2[] = {"XD", "FFA", "NNS", "KIP", "ZCF"};
    string row3[] = {"B", "WA", "RW", "H", "SR"};
    string row4[] = {"V", "S", "RQ", "W", "G"};
    string row5[] = {"MJK", "KH", "ER", "NJM", "H"};
    string row6[] = {"FW", "SDE", "D", "XZV", "JN"};
    string row7[] = {"UY", "FHB", "A", "XFG", "MB"};
    string row8[] = {"I", "QG", "XA", "CZ", "VC"};

    string *diceArray[] = {row0, row1, row2, row3, row4, row5, row6, row7, row8};

    lex.insert("abqewngjk");
    lex.insert("fhbadxzv");
    lex.insert("czvcmbjnh");
    lex.insert("iuyfw");
    lex.insert("rqwgnjm");
    lex.insert("nnskipsrg");
    lex.insert("doesNotExistZ");
    lex.insert("doesNotExistX");

    player->setBoard(9, 5, diceArray);

    for (short r = 0; r < 9; r++)
    {
        for (short c = 0; c < 5; c++)
        {
            testString.append(diceArray[r][c]);
            positions.push_back(r*5 + c);
        }
        // lex.insert(testString);
        
	/*cout << "Positions: ";
        for (int i: positions)
            cout << i << " ";
        cout << endl;/**/ 

        vector<int> temp = player->isOnBoard(testString); 

        /*cout << "player->isOnBoard() = ";
        for (int i: temp)
            cout << i << " ";
        cout << endl; /**/  
        assert(temp.size() != 0); 

        if (player->isOnBoard(testString) != positions)
        {
            cout << "ERROR: isOnBoard failed for " << testString << endl;
            failed = true;
        }

        positions.clear();
        testString.clear();
    }

    player->buildLexicon(lex);
    if (!player->getAllValidWords(0, &validWords))
    {
        cout << "ERROR: getAllValidWords returned false when it should not have" << endl;
        failed = true;
    }
    for (auto &zod : validWords)
    {
        if (lex.find(zod) == lex.end())
        {
            cout << "ERROR: " << zod << " was in the set returned by getAllValidWords but not in the lexicon." << endl;
            failed = true;
        }
    }

    if (validWords.size() != (lex.size()-2))
    {
        cout << "ERROR: getAllValidWords did not did return a set with the correct number of words in it" << endl;
        failed = true;
    }
    validWords.clear();
    lex.clear();
    // 1x1 TEST //

    string rowQ[] = {"A"};
    string *diceArray2[] = {rowQ};
    player->setBoard(1, 1, diceArray2);
    vector<int> empty;
    testString = "A";
    positions.clear();
    positions.push_back(0);
    if (player->isOnBoard(testString) != positions)
    {
        cout << "ERROR: \"A\" was not in the right place on the board in the 1x1 test " << endl;
        failed = true;
    }
    if (player->isOnBoard("test") != empty)
    {
        cout << "ERROR: The 1x1 board found a word that does not exist on the board " << endl;
        failed = true;
    }

    // Default Tests //

    string wordA("a");
    string wordX("x");
    lex.insert(wordA);
    lex.insert("z");
    string rowF[] = {"D","C"};
    string rowG[] = {"b","A"};
    string *diceArray3[] = {rowF,rowG};

    player->buildLexicon(lex);

    player->setBoard(2,2,diceArray3);

    if (player->isInLexicon(wordX))
    {
        std::cerr << "Apparent problem with isInLexicon #1." << std::endl;
        failed = true;;
    }
    if (!player->isInLexicon(wordA))
    {
        std::cerr << "Apparent problem with isInLexicon #2." << std::endl;
        failed = true;;
    }

    if (player->isOnBoard(wordX).size() > 0)
    {
        std::cerr << "Apparent problem with isOnBoard #1." << std::endl;
        failed = true;;
    }

    positions.clear();
    positions = player->isOnBoard(wordA);
    if (positions.size() != 1 || positions[0] != 3)
    {
        std::cerr << "Apparent problem with isOnBoard #2." << std::endl;
        failed = true;;
    }


    if (!player->getAllValidWords(0,&validWords))
    {
        std::cerr << "Apparent problem with getAllValidWords #1." << std::endl;
        failed = true;;
    };
    if (validWords.size() != 1 || validWords.count(wordA) != 1)
    {
        cout << lex.size() << endl;
        cout << lex.count(wordA) << endl;
        std::cerr << "Apparent problem with getAllValidWords #2." << std::endl;
        failed = true;;
    }
    positions.clear();
    validWords.clear();
    lex.clear();

    // Is on board test. Could be written a lot better.
    // But it's just a hacked together test
    string row01[] = {"T","H","L","I"};
    string row11[] = {"R","E","A","D"};
    string row21[] = {"I","L","M","O"};
    string row31[] = {"F","P","S","N"};
    string *board[] = {row01,row11,row21,row31};

    player->setBoard(4,4,board);
    std::vector<int>checkVector;
    std::vector<int>checkVector2;
    std::vector<int>checkVector3;

    checkVector = player->isOnBoard("TRIP");
    checkVector2.push_back(0);
    checkVector2.push_back(4);
    checkVector2.push_back(8);
    checkVector2.push_back(13);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: TRIP was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("mad");
    checkVector2.push_back(10);
    checkVector2.push_back(6);
    checkVector2.push_back(7);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: mad was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("Help");
    checkVector2.push_back(1);
    checkVector2.push_back(5);
    checkVector2.push_back(9);
    checkVector2.push_back(13);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: Help was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("lamE");
    checkVector2.push_back(2);
    checkVector2.push_back(6);
    checkVector2.push_back(10);
    checkVector2.push_back(5);

    checkVector3.push_back(9);
    checkVector3.push_back(6);
    checkVector3.push_back(10);
    checkVector3.push_back(5);

    if (checkVector != checkVector2 && checkVector != checkVector3)
    {
        cout << "ERROR: lamE was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();
    checkVector3.clear();

    checkVector = player->isOnBoard("dOmE");
    checkVector2.push_back(7);
    checkVector2.push_back(11);
    checkVector2.push_back(10);
    checkVector2.push_back(5);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: dOmE was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("FiRe");
    checkVector2.push_back(12);
    checkVector2.push_back(8);
    checkVector2.push_back(4);
    checkVector2.push_back(5);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: FiRe was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("flip");
    checkVector2.push_back(12);
    checkVector2.push_back(9);
    checkVector2.push_back(8);
    checkVector2.push_back(13);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: flip was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("real");
    checkVector2.push_back(4);
    checkVector2.push_back(5);
    checkVector2.push_back(6);
    checkVector2.push_back(2);

    checkVector3.push_back(4);
    checkVector3.push_back(5);
    checkVector3.push_back(6);
    checkVector3.push_back(9);
    if (checkVector != checkVector2 && checkVector != checkVector3)
    {
        cout << "ERROR: real was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();
    checkVector3.clear();

    checkVector = player->isOnBoard("ream");
    checkVector2.push_back(4);
    checkVector2.push_back(5);
    checkVector2.push_back(6);
    checkVector2.push_back(10);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: ream was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("HEAL");
    checkVector2.push_back(1);
    checkVector2.push_back(5);
    checkVector2.push_back(6);
    checkVector2.push_back(2);

    checkVector3.push_back(1);
    checkVector3.push_back(5);
    checkVector3.push_back(6);
    checkVector3.push_back(9);
    if (checkVector != checkVector2 && checkVector != checkVector3)
    {
        cout << "ERROR: HEAL was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();
    checkVector3.clear();

    checkVector = player->isOnBoard("had");
    checkVector2.push_back(1);
    checkVector2.push_back(6);
    checkVector2.push_back(7);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: had was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("hAm");
    checkVector2.push_back(1);
    checkVector2.push_back(6);
    checkVector2.push_back(10);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: hAm was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("son");
    checkVector2.push_back(14);
    checkVector2.push_back(11);
    checkVector2.push_back(15);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: son was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("LID");
    checkVector2.push_back(2);
    checkVector2.push_back(3);
    checkVector2.push_back(7);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: LID was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("dame");
    checkVector2.push_back(7);
    checkVector2.push_back(6);
    checkVector2.push_back(10);
    checkVector2.push_back(5);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: dame was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("team");
    checkVector2.push_back(0);
    checkVector2.push_back(5);
    checkVector2.push_back(6);
    checkVector2.push_back(10);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: team was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    // Corner Test Case

    string row04[] = {"C", "A", "X", "X", "X"};
    string row14[] = {"R", "T", "X", "X", "X"};
    string row24[] = {"X", "X", "X", "X", "X"};
    string row34[] = {"X", "X", "X", "X", "X"};
    string row44[] = {"X", "X", "X", "X", "X"};
    string row54[] = {"X", "X", "X", "X", "X"};

    string *diceArray4[] = {row04, row14, row24, row34, row44, row54};

    lex.insert("cart");
    lex.insert("car");
    lex.insert("cat");
    lex.insert("arc");
    lex.insert("art");
    lex.insert("at");
    lex.insert("a");
    lex.insert("act");
    lex.insert("tar");
    lex.insert("rat");

    player->buildLexicon(lex);
    player->setBoard(6, 5, diceArray4);

    for (auto &zod : lex)
    {
        if (!player->isInLexicon(zod))
        {
            cout << "ERROR: " << zod << " was not found in the Lexicon" << endl;
            failed = true;
        }
    }

    if (!player->getAllValidWords(1, &validWords))
    {
        cout << "ERROR: getAllValidWords returned false when it should not have" << endl;
        failed = true;
    }

    if (validWords.size() != lex.size())
    {
        cout << "ERROR: getAllValidWords did not did return a set with the correct number of words in it" << endl;
        failed = true;
    }

    for (auto &zod : lex)
    {
        if (validWords.find(zod) == validWords.end())
        {
            cout << "ERROR: " << zod << " was in the lexicon and on the board but was not found by getAllValidWords" << endl;
            failed = true;
        }
    }

    validWords.clear();
    lex.clear();

    checkVector = player->isOnBoard("CART");
    checkVector2.push_back(0);
    checkVector2.push_back(1);
    checkVector2.push_back(5);
    checkVector2.push_back(6);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: CART was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("CAR");
    checkVector2.push_back(0);
    checkVector2.push_back(1);
    checkVector2.push_back(5);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: CAR was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("CAT");
    checkVector2.push_back(0);
    checkVector2.push_back(1);
    checkVector2.push_back(6);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: CAT was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("ARC");
    checkVector2.push_back(1);
    checkVector2.push_back(5);
    checkVector2.push_back(0);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: ARC was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("ART");
    checkVector2.push_back(1);
    checkVector2.push_back(5);
    checkVector2.push_back(6);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: ART was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("AT");
    checkVector2.push_back(1);
    checkVector2.push_back(6);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: AT was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("A");
    checkVector2.push_back(1);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: A was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("ACT");
    checkVector2.push_back(1);
    checkVector2.push_back(0);
    checkVector2.push_back(6);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: ACT was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("TAR");
    checkVector2.push_back(6);
    checkVector2.push_back(1);
    checkVector2.push_back(5);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: TAR was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    checkVector = player->isOnBoard("RAT");
    checkVector2.push_back(5);
    checkVector2.push_back(1);
    checkVector2.push_back(6);
    if (checkVector != checkVector2)
    {
        cout << "ERROR: RAT was not found on the board properly. " << endl;
        failed = true;
    };
    checkVector.clear();
    checkVector2.clear();

    std::ifstream in("lex.txt");

    // Load the lexicon from file
    string word;
    set<string> results;
    while (std::getline(in, word))
        lex.insert(word);
    in.close();

    // setup the board
    int rows;
    int cols;
    in.open("brd.txt");
    in >> rows;
    in >> cols;
    std::string **brd = new std::string*[rows];

    for (int i = 0; i < rows; ++i)
    {
        std::string *row6 = new std::string[cols];

        for (int j = 0; j < cols; ++j)
        {
            in >> row6[j];
        }
        brd[i] = row6;
    }

    in.close();

    // Store results into a set so we can compare it to what getAllValidWords() returns
    in.open("results.txt");
    while (std::getline(in, word))
        results.insert(word);
    in.close();

    player->buildLexicon(lex);
    player->setBoard(rows, cols, brd);

    clock_t start;
    double duration;
    start = clock();
    player->getAllValidWords(2, &validWords);
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;

    cout << "Your implementation of getAllValidWords took " << duration << " seconds to find all 5450 words" << endl;

    if (!(duration < 10))
    {
        cout << "ERROR: getAllValidWords was not completed in under 10 seconds" << endl;
        failed = true;
    }

    if (!(duration < 5))
    {
        cout << "ERROR: getAllValidWords was not completed in under 5 seconds" << endl;
        failed = true;
    }

    if (validWords.size() != results.size())
    {
        cout << "ERROR: getAllValidWords did not find the correct number of words" << endl;
        failed = true;
    }

    for (auto zod : results)
    {
        if (validWords.find(zod) == validWords.end())
        {
            cout << "ERROR: " << zod << " was not found in getAllValidWords when it should have been" << endl;
            failed = true;
        }
    }

    if (failed)
        cout << "FAILURE! At least one test did not pass. " << endl;
    else
        cout << "SUCCESS! All tests passed. " << endl;

    for (int zod = 0; zod < rows; ++zod)
        delete[] brd[zod];
    delete[] brd;
    delete player;
    return 0;
}
