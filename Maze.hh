/* Gregoire DUCHARME */
/* 03/08/2016 */

#ifndef _MAZE_HH_
# define _MAZE_HH_

# include <iostream>
# include <fstream>
# include <vector>
# include <random>
# include "Edge.hh"

/* Int defined to make the switch condition more clear */
const int LEFT = 0;
const int RIGHT = 1;
const int UP = 2;
const int DOWN = 3;

const bool HORIZONTAL = true;
const bool VERTICAL = false;

class Maze {
  int	_width = 0;
  int	_height = 0;
  unsigned int	_countEdges = 0;
  std::vector<Edge>	_edges;
  bool checkMap(std::vector<std::vector<int>>) const;
  bool initValues(int, int, unsigned int = 0);
  void fillMapAldousBroder(std::vector<std::vector<int>>, std::mt19937);
  void fillMapEller(std::vector<std::vector<int>>, std::mt19937);
  void createEdgeEller(int, bool, std::vector<std::vector<int>>);

public:
  enum	algorithm_type {
    ALDOUS_BRODER = 0,
    ELLER = 1
  };
  Maze() {}
  bool saveToSvgFile(std::string) const;
  bool saveToBinaryFile(std::string) const;
  bool isValid() const;
  bool loadFromBinaryFile(std::string);
  bool loadNewMaze(int, int, int, algorithm_type);
};

#endif
