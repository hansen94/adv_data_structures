#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "UndirectedGraph.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"

/**
 * Entry point into the netplan program.
 *
 * -Reads a file from the filesystem according to the specification for
 *  PA3, creating an UndirectedGraph.
 * -Finds the total cost & ping time of the graph as presented in the input
 *  file.
 * -Determines the minimum cost graph from the original graph.
 * -Finds the total cost & ping time of the minimum cost graph.
 * -Finds the change of cost & ping time from the original graph to the
 *  minimum cost graph.
 * -Prints the results to stdout.
 *
 * Usage:
 *   ./netplan infile
 *
 */
int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " infile" << std::endl;
        return EXIT_FAILURE;
    }
    
    std::ifstream in(argv[1]);
    if (!in) {
        std::cerr << "Unable to open file for reading." << std::endl;
        return EXIT_FAILURE;
    }
    
    UndirectedGraph ug;

    while (!in.eof()) {
      std::string neta, netb;
      unsigned int cost, late;

      /* BUG: Infinite for misformed input
       */

      in >> neta;
      in >> netb;
      in >> cost;
      in >> late;

      if (neta != "" && netb != "")
	ug.addEdge(neta, netb, cost, late);
    }

    //std::cout << ug << std::endl << std::endl;
    UndirectedGraph minug = ug.minSpanningTree();
    //std::cout << minug << std::endl;

    unsigned int tCost, mCost, tDist, mDist;
    
    std::cout << (tCost = ug.totalEdgeCost()) << std::endl;


    std::cout << (mCost = minug.totalEdgeCost()) << std::endl;
    std::cout << (tCost - mCost) << std::endl;


    std::cout << (tDist = ug.totalDistance()) << std::endl;
    std::cout << (mDist = minug.totalDistance()) << std::endl;
    std::cout << (mDist - tDist) << std::endl;

    return EXIT_SUCCESS;
}
