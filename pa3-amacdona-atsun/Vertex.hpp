#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <string>
#include <unordered_map>
#include <ostream>

#include "Edge.hpp"

/**
 * Represents a Vertex in a graph.
 *
 * Vertices are connected to other Vertices via Edges. Each Vertex
 * maintains a collection of all Edges that originate from it.
 */
class Vertex {
  // Graph needs access to Edge map for Dijkstra/Prim algorithms.
  friend class UndirectedGraph;
  friend std::ostream& operator<< (std::ostream &os, const Vertex &v);
    
public:
  typedef std::unordered_map<std::string, Edge> edgemap;

  Vertex();

  /**
   * Initialize the Vertex with the given name.
   */
  Vertex(const std::string &name);

  /**
   * Adds an edge to .this and .to
   * 
   * Add edge to this Vertex. If an edge already exists to the given
   * vertex, updates the cost and length of the edge to match the
   * passed parameters.
   */
  bool addEdge(Vertex *to, unsigned int cost, unsigned int length);
    
  /**
   * Returns the Vertex's name.
   */
  const std::string &getName() const;

  /** Set the Vertex name
   * 
   */
  void setName(const std::string &str);
    
  /**
   * Gets the Vertex's distance value.
   */
  unsigned int getDistance() const;

  /**
   * Sets the Vertex's distance value.
   */
  void setDistance(unsigned int distance);
    
  /**
   * Gets the Vertex's visited state.
   */
  bool wasVisited() const;

  /**
   * Sets the Vertex's visited state.
   */
  void setVisited(bool visited);

  /**
   * Clears all edges from this Vertex.
   */
  void clearEdges();

  /** Extract the minmium Edge
   */
  Edge minEdge();

  /**
   * Gets total cost of all edges terminating at this Vertex.
   */
  unsigned int totalEdgeCost() const;
    
private:

  /**
   * Returns a reference to the internal map of Edges.
   * Used by UndirectedGraph for Dijkstra/Prim algorithms.
   */
  const edgemap& getEdges() const;

  /**
   * Name of this Vertex.
   */
  std::string name;

  Vertex *prev;
    
  /**
   * Distance of this Vertex from initial Vertex.
   * Used by Dijkstra's algorithm.
   */
  unsigned int distance;
    
  /**
   * Whether this node has been visited.
   * Used by Prim's algorithm.
   */
  bool visited;

  /**
   * Map of adjacent Vertex name to Edge describing the adjacency.
   */
  edgemap edges;
};

std::ostream& operator<< (std::ostream &os, const Vertex &v);
#endif
