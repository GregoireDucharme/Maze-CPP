/* Gregoire DUCHARME */
/* 03/08/2016 */

#include "Edge.hh"

/* 
// Operator overloadgin to allow usage:
// filename << edge
*/
std::ostream&	operator<<(std::ostream& os, Edge edge)
{
  os << "<line x1=\""<< edge.getxA() * SIZE_RATIO << "\"";
  os << " x2=\"" << edge.getxB() * SIZE_RATIO << "\"";
  os << " y1=\"" << edge.getyA() * SIZE_RATIO << "\"";
  os << " y2=\"" << edge.getyB() * SIZE_RATIO << "\"";
  os <<  " stroke=\"white\" stroke-width=\"" << SIZE_RATIO / 2 <<"\" />";
  return os;
}

Edge::Edge(int xA, int yA, int xB, int yB)
{
  _xA = xA;
  _yA = yA;
  _xB = xB;
  _yB =yB;
}

int Edge::getxA() const
{
  return _xA;
}
int Edge::getyA() const
{
  return _yA;
}
int Edge::getxB() const
{
  return _xB;
}
int Edge::getyB() const
{
  return _yB;
}
