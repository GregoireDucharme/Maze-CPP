/* Gregoire DUCHARME */
/* 18/10/2016 */

#include "Cell.hh"


/* See .hh file for constructor */

/*
// Operator overloadgin to allow usage:
// filename << cell
*/
std::ostream&	operator<<(std::ostream& os, Cell *cells)
{
  os << "<line";
  os  << " x1=\""<< (cells[0].getX() / 2 + 0.5) * SIZE_RATIO <<"\"";
  os << " y1=\""<< (cells[0].getY() / 2 + 0.5) * SIZE_RATIO <<"\"";
  os << " x2=\""<< (cells[1].getX() / 2 + 0.5) * SIZE_RATIO <<"\"";
  os << " y2=\""<< (cells[1].getY() / 2 + 0.5) * SIZE_RATIO <<"\"";
  os << " stroke=\"red\" stroke-width=\"" <<
    SIZE_RATIO / 2 << "\" />" << std::endl;
  return os;
}

int Cell::getX() const
{
  return _x;
}

int Cell::getY() const
{
  return _y;
}

int Cell::getIndex() const
{
  return _index;
}

void Cell::setIndex(int index)
{
  _index = index;
}

int Cell::getDeepness() const
{
  return _deepness;
}

/* Check if the current cell is present in the path given in parameter */
bool Cell::isNotIn(std::vector<Cell> path) const
{
  for (unsigned int i = 0; i < path.size(); i++) {
    if (path[i].getX() == _x && path[i].getY() == _y)
      return false;
  }
  return true;
}
