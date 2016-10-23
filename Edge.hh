/* Gregoire DUCHARME */
/* Yixuan Zhang */
/* 23/10/2016 */

#ifndef _EDGE_HH_
# define _EDGE_HH_

# include <iostream>
# include "SizeRatio.hh"

class Edge {

  int	_xA;
  int	_yA;
  int	_xB;
  int	_yB;

public:
  Edge(int, int, int, int);
  int getxA() const;
  int getyA() const;
  int getxB() const;
  int getyB() const;
};

std::ostream& operator<<(std::ostream& os, Edge edge);

#endif
