#include "Vertex.hpp"


Vertex::Vertex() {
}

/**
 * Initialize the Vertex with the given name.
 */
Vertex::Vertex(const std::string &name) {
  this->name = name;
}

/**
 * Add an edge to this Vertex. If an edge already exists to the given
 * vertex, updates the cost and length of the edge to match the
 * passed parameters.
 */
bool Vertex::addEdge(Vertex *to,
		     unsigned int cost,
		     unsigned int length) {
  this->edges[to->getName()] = Edge(this, to, cost, length);

  return true;
}
    
/**
 * Returns the Vertex's name.
 */
const std::string& Vertex::getName() const {
  return this->name;
}

/** Set the Vertex name
 * 
 */
void Vertex::setName(const std::string &str) {
  this->name = str;
}

    
/**
 * Gets the Vertex's distance value.
 */
unsigned int Vertex::getDistance() const {
  return this->distance;
}

/**
 * Sets the Vertex's distance value.
 */
void Vertex::setDistance(unsigned int distance) {
  this->distance = distance;
}
    
/**
 * Gets the Vertex's visited state.
 */
bool Vertex::wasVisited() const {
  return this->visited;
}

/**
 * Sets the Vertex's visited state.
 */
void Vertex::setVisited(bool visited) {
  this->visited = visited;
}


/**
 * Clears all edges from this Vertex.
 */
void Vertex::clearEdges() {
  this->edges.clear();
}

/**
 * Gets total cost of all edges terminating at this Vertex.
 */
unsigned int Vertex::totalEdgeCost() const {
  unsigned int total = 0;
  
  for (Vertex::edgemap::const_iterator itr = this->edges.begin();
       itr != this->edges.end();
       itr++) {
    total += itr->second.getCost();
  }
  
  return total;
}
    

/**
 * Returns a reference to the internal map of Edges.
 * Used by UndirectedGraph for Dijkstra/Prim algorithms.
 */
const Vertex::edgemap& Vertex::getEdges() const {
  return this->edges;
}

std::ostream& operator<< (std::ostream &os, const Vertex &v) {
  for (Vertex::edgemap::const_iterator itr = v.edges.begin();
       itr != v.edges.end();
       itr++)
    os << itr->second;

  return os;
}
