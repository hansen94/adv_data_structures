/** Unit Testing for every class
 * \author Aidan Macdonald
 * 
 * 
 */


#include <iostream>
#include <iomanip>
#include <unordered_map>
#include "UndirectedGraph.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"


#define TEST(cmd) \
  std::cout << std::setw(40) << std::left \
  << "   " << #cmd << std::right \
  << (cmd ? "True" : "False") << std::endl;


/** Define separate test case functions here
 */


bool testEdge();
bool testVertex();
bool testUndirectedGraph();

int main() {
  TEST(testEdge());
  TEST(testVertex());
  TEST(testUndirectedGraph());

  return 0;
}


bool testEdge() {


  return false;
}

bool testVertex() {
  return false;
}

bool testUndirectedGraph() {
  return false;
}
