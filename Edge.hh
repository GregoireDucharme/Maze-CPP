/* Gregoire DUCHARME */
/* 03/08/2016 */

#ifndef _EDGE_HH_
# define _EDGE_HH_

# include <iostream>

/* Define the size ratio for the SVG file */
const int SIZE_RATIO = 26;

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
