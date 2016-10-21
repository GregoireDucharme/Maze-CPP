/* Gregoire DUCHARME */
/* 18/10/2016 */

#ifndef CELL_HH_
# define CELL_HH_

# include <iostream>
# include <vector>
# include "SizeRatio.hh"

class Cell {
  int _x;
  int _y;
  int _index;
  int _deepness;

public:
  int getX() const;
  int getY() const;
  int getIndex() const;
  void setIndex(int);
  int getDeepness() const;
  bool isNotIn(std::vector<Cell>) const;
  Cell(int x = 0, int y = 0, int index = 0, int deepness = 0){
    _x = x;
    _y = y;
    _index = index;
    _deepness = deepness;
  }
  Cell(const Cell &old) {
    _x = old.getX();
    _y = old.getY();
    _index = old.getIndex();
    _deepness = old.getDeepness();
  }
};

std::ostream& operator<<(std::ostream& os, Cell *cell);

#endif /* CELL_HH_ */
