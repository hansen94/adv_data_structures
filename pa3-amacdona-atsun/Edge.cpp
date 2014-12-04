#include "Edge.hpp"
#include "Vertex.hpp"

Edge::Edge() {
  this->from = nullptr;
  this->to = nullptr;
}

Edge::Edge(Vertex *from, Vertex *to,
            unsigned int cost,
            unsigned int length): from(from), to(to), 
                                  cost(cost), length(length) {
}

Edge::Edge(const Edge &e) {
  this->from = e.from;
  this->to = e.to;
  this->cost = e.cost;
  this->length = e.length;
}

Edge& Edge::operator= (const Edge &e) {
  this->from = e.from;
  this->to = e.to;
  this->cost = e.cost;
  this->length = e.length;

  return *this;
}
            
Vertex* Edge::getFrom() const {
  return this->from;
}

Vertex* Edge::getTo() const { 
  return this->to;
}

unsigned int Edge::getCost() const { 
  return this->cost;
}

unsigned int Edge::getLength() const {
  return this->length;
}

void Edge::setLength(unsigned int length) {
  this->length = length;
}

/*
 * Compares this Edge to another Edge. Suitable for
 * use with a priority queue where Edges with the lowest
 * weight have the highest priority.
 *
 * Returns true if this Edge's cost is more than
 * right's cost.
 */
bool Edge::operator<(const Edge &right) const {
  return (this->cost > right.cost);

  /* if (this->cost > right.cost)
    return false;
  else if (this->cost < right.cost)
    return true;
  else if (this->to != right.from || this->from != right.to)
    return !(this->from < right.from);
    return true; /**/
}


std::ostream& operator<< (std::ostream & os, const Edge &e) {
  os << e.getFrom()->getName() << " "
     << e.getTo()->getName() << " "
     << e.getCost() << " "
     << e.getLength() << std::endl;

  return os;
}



            
            
