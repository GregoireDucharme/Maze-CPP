/* Gregoire DUCHARME */
/* 18/10/2016 */

#include "Cell.hh"

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

bool Cell::isNotIn(std::vector<Cell> path) const
{
  for (unsigned int i = 0; i < path.size(); i++) {
    if (path[i].getX() == _x && path[i].getY() == _y)
      return false;
  }
  return true;
}
