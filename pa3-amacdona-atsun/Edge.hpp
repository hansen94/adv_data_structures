#ifndef EDGE_HPP
#define EDGE_HPP


#include <ostream>

class Vertex;

/**
 * Represents an edge in a graph.
 *
 * Maintains pointers to the vertices that the edge originates 
 * from and terminates at. Edges have both a cost and a length,
 * which are both non-negative integers.
 *
 * Follows value semantics, so can be copy constructed.
 */
class Edge {
public:

  /** Default Constructor
   * 
   */
  Edge();

  /**
   * Constructs an Edge from the given parameters.
   */
  Edge(Vertex *from, Vertex *to,
       unsigned int cost,
       unsigned int length);

  /** Edge Assignment operator
   * Sets pointers, cost, and length
   */
  Edge& operator= (const Edge &e);

  /** Edge Copy Constructor
   * Sets pointers, cost, and length
   */
  Edge(const Edge &e);

  /**
   * Returns a pointer to the Vertex that this Edge originates
   * from.
   */
  Vertex *getFrom() const;
    
  /**
   * Returns a pointer to the Vertex that this Edge terminates
   * at.
   */
  Vertex *getTo() const;

  /**
   * Sets the cost of this Edge.
   */
  void setCost(unsigned int cost);

  /**
   * Returns the cost of this Edge.
   */
  unsigned int getCost() const;

  /**
   * Sets the length of this Edge.
   */
  void setLength(unsigned int length);

  /**
   * Returns the length of this Edge.
   */
  unsigned int getLength() const;

  /*
   * Compares this Edge to another Edge. Suitable for
   * use with a priority queue where Edges with the lowest
   * weight have the highest priority.
   *
   * Returns true if this Edge's cost is more than
   * right's cost.
   */
  bool operator<(const Edge &right) const;
    
private:
  /**
   * Vertex that this Edge originates from.
   */
  Vertex *from;

  /**
   * Vertex that this Edge terminates at.
   */
  Vertex *to;

  /**
   * Cost of this Edge.
   */
  unsigned int cost;

  /**
   * Length of this Edge.
   */
  unsigned int length;
};

std::ostream& operator<< (std::ostream & os, const Edge &e);

#endif
