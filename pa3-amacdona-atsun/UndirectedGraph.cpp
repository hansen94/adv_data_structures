#include "UndirectedGraph.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"
#include <iostream>
#include <set>
#include <queue>
#include <limits.h>

// Method implementations here
/**
 * Constructs an empty UndirectedGraph with no vertices and
 * no edges.
 */
UndirectedGraph::UndirectedGraph() {
  // Does nothing yet
}

/** Copy Constructor
 */
UndirectedGraph::UndirectedGraph(const UndirectedGraph &ug) {
  this->vertices = ug.vertices;
}


/** Assignment Constructor
 */
UndirectedGraph& UndirectedGraph::operator= (const UndirectedGraph &ug) {
  this->vertices = ug.vertices;

  return *this;
}


/**
 * Destructs an UndirectedGraph.
 */
UndirectedGraph::~UndirectedGraph() {
  for (UndirectedGraph::vertexmap::iterator itr
	 = this->vertices.begin();
       itr != this->vertices.end();
       itr++)
    delete itr->second;
}
    
/**
 * Inserts an edge into the graph. If an edge already exists between
 * the vertices, updates the cost and length of the edge to match the
 * passed parameters.
 *
 * If either of the named vertices does not exist, it is created.
 */
void UndirectedGraph::addEdge(const std::string &from, const std::string &to,
			      unsigned int cost, unsigned int length) {
  if (this->vertices.find(from) == this->vertices.end())
    this->vertices[from] = new Vertex(from);

  if (this->vertices.find(to) == this->vertices.end())
    this->vertices[to] = new Vertex(to);
    
  this->vertices[from]->setName(from); // In case a vertex doesn't exist, makes defaults and names it
  this->vertices[to]->setName(to);

  this->vertices[from]->addEdge(this->vertices[to], cost, length);
  this->vertices[to]->addEdge(this->vertices[from], cost, length);
}

void UndirectedGraph::addEdge(const Edge &e) {
  this->addEdge(e.getFrom()->getName(), e.getTo()->getName(),
		e.getCost(), e.getLength());
}

/**
 * Returns the total cost of all edges in the graph.
 *
 * Since this graph is undirected, is calcualted as the cost
 * of all Edges terminating at all Vertices, divided by 2.
 */
unsigned int UndirectedGraph::totalEdgeCost() const {
  unsigned int total = 0;
  
  for (UndirectedGraph::vertexmap::const_iterator itr 
	 = this->vertices.begin();
       itr != this->vertices.end();
       itr++)
    total += itr->second->totalEdgeCost();

  return total/2;
}
    
std::ostream& operator<< (std::ostream &os, std::priority_queue<Edge> edges) {
  os << "Queue Size " << edges.size() << std::endl;
  while (edges.size() > 0) {
    os << edges.top();
    edges.pop();
  }

  return os;
}

/**
 * Removes all edges from the graph except those necessary to
 * form a minimum cost spanning tree of all vertices using Prim's
 * algorithm.
 *
 * The graph must be in a state where such a spanning tree
 * is possible. To call this method when a spanning tree is
 * impossible is undefined behavior.
 */
UndirectedGraph UndirectedGraph::minSpanningTree() {
  // Define based on the Wikipedia Pseudocode
  UndirectedGraph nug;
  
  std::priority_queue<Edge> edges;

  for (vertexmap::iterator vi = this->vertices.begin();
       vi != this->vertices.end();
       vi++)
    vi->second->setVisited(false);

  Vertex *cur = this->vertices.begin()->second;
  cur->setVisited(true);
  for (Vertex::edgemap::iterator ei = cur->edges.begin();
       ei != cur->edges.end();
       ei++)
    edges.push(ei->second);
  
  while (!edges.empty() && nug.vertices.size() < this->vertices.size()) {
    Edge small = edges.top();
    edges.pop();
    Vertex *to = small.getTo();
    
    if (to->wasVisited())
      continue;
    else {
      to->setVisited(true);
      nug.addEdge(small);
      for (Vertex::edgemap::iterator ei = to->edges.begin();
	   ei != to->edges.end();
	   ei++)
	if (!ei->second.getTo()->wasVisited())
	  edges.push(ei->second);
    }
  } // END WHILE

  return nug;
}
    
/**
 * Determines the combined distance from the given Vertex to all
 * other Vertices in the graph using Dijkstra's algorithm.
 *
 * Returns max possible distance if the given Vertex does not appear
 * in the graph, or if any of the Vertices in the graph are not
 * reachable from the given Vertex. Otherwise, returns the combined
 * distance.
 */
unsigned int UndirectedGraph::totalDistance(const std::string &from) {
  std::priority_queue<vertpair, std::vector<vertpair>, DijkstraVComp> verts;

  verts.push(vertpair(this->vertices[from], 0));
  this->vertices[from]->setDistance(0);
  verts.top().first->setVisited(false);

  for (vertexmap::iterator itr = this->vertices.begin();
       itr != this->vertices.end();
       itr++) {
    if (itr->first != from) {
      itr->second->setVisited(false);
      itr->second->setDistance(UINT_MAX);
    }
  } // END FOR

  while (verts.size() > 0) { // while Q is not empty:
    Vertex *v = verts.top().first;
    verts.pop();
    if (v->wasVisited())
      continue;

    v->setVisited(true);
    for (Vertex::edgemap::const_iterator ei = v->getEdges().begin();
	 ei != v->getEdges().end();
	 ei++) {
      unsigned int alt = v->getDistance() + ei->second.getLength();
      Vertex *next = ei->second.getTo();

      if (alt < next->getDistance()) {
	next->setDistance(alt);
	verts.push(vertpair(next, alt));
      }
    } //END FOR
  } //END WHILE


  unsigned int total = 0;
  for (vertexmap::iterator itr = this->vertices.begin();
       itr != this->vertices.end();
       itr++)
    total += itr->second->getDistance();

  /*
 1  function Dijkstra(Graph, source):
 2      dist[source]  := 0                     // Distance from source to source
 3      for each vertex v in Graph:            // Initializations
 4          if v ? source
 5              dist[v]  := infinity           // Unknown distance function from source to v
 6              previous[v]  := undefined      // Previous node in optimal path from source
 7          end if 
 8          add v to Q                         // All nodes initially in Q (unvisited nodes)
 9      end for
10      
11      while Q is not empty:                  // The main loop
12          u := vertex in Q with min dist[u]  // Source node in first case
13          remove u from Q 
14          
15          for each neighbor v of u:           // where v has not yet been removed from Q.
16              alt := dist[u] + length(u, v)
17              if alt < dist[v]:               // A shorter path to v has been found
18                  dist[v]  := alt 
19                  previous[v]  := u 
20              end if
21          end for
22      end while
23      return dist[], previous[]
24  end function
  */

  return total;
}
    
/**
 * Determines the combined distance from all Vertices to all other
 * Vertices in the graph.
 *
 * Returns max possible distance if the graph is not connected.
 */
unsigned int UndirectedGraph::totalDistance() {
  unsigned int total = 0;

  for (vertexmap::iterator itr = this->vertices.begin();
       itr != this->vertices.end();
       itr++)
    total += this->totalDistance(itr->first);
  
  return total;
}

std::ostream& operator<< (std::ostream& os, const UndirectedGraph &ug) {
  
  for (UndirectedGraph::vertexmap::const_iterator itr = ug.vertices.begin();
       itr != ug.vertices.end();
       itr++) {
    os << *itr->second;
  }   
  
  return os;
}
 
  /**
   * Comparison functor for use with Dijkstra's algorithm. Allows Vertices
   * to be added to a priority queue more than once, with different weights.
   *
   * Each pair represents a Vertex and its weight when it was added to the
   * queue. This guarantees that the weight used to order the Vertices in
   * the queue never changes (a required invariant of a priority queue),
   * even though the weight of the Vertex itself may change.
   *
   * Returns true if left's weight when it was inserted into the queue is
   * higher than right's weight when it was inserted into the queue.
   */

 bool UndirectedGraph::DijkstraVComp::operator()(const UndirectedGraph::vertpair &left,
						 const UndirectedGraph::vertpair &right) {

   return left.second > right.second;
 }
