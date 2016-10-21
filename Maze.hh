/* Gregoire DUCHARME */
/* 03/08/2016 */

#ifndef _MAZE_HH_
# define _MAZE_HH_

# include <iostream>
# include <fstream>
# include <vector>
# include <random>
# include "Edge.hh"
# include "Cell.hh"

/* Int defined to make the switch condition more clear */
const int LEFT = 0;
const int RIGHT = 1;
const int UP = 2;
const int DOWN = 3;

/* Use in eller algorithm to know the way of the edges */
const bool HORIZONTAL = true;
const bool VERTICAL = false;

class Maze {
  bool solvePM();
  bool solvePE();
  bool solvePB();
  bool solvePD();
  int	_width = 0;
  int	_height = 0;
  unsigned int	_countEdges = 0;
  std::vector<Edge>	_edges;
  std::string _filename = "";
  bool checkMap(std::vector<std::vector<int>>) const;
  bool initValues(int, int, unsigned int = 0);
  void fillMapAldousBroder(std::vector<std::vector<int>>, std::mt19937);
  void fillMapEller(std::vector<std::vector<int>>, std::mt19937);
  void createEdgeEller(int, bool, std::vector<std::vector<int>>);
  bool checkCell(Cell);
  bool getCells(std::vector<Cell>&, std::vector<Cell>);
  void saveSolvedToSvg(std::vector<Cell>);

public:
  /* Enum use to make condition more clear */
  enum algorithm_type {
    ALDOUS_BRODER = 0,
    ELLER = 1
  };
  enum solving_type {
    NONE = -1,
    PM = 0,
    PE = 1,
    PB = 2,
    PD = 3
  };
  Maze() {
  }
  bool saveToSvgFile(std::string);
  bool saveToBinaryFile(std::string) const;
  bool isValid() const;
  bool loadFromBinaryFile(std::string);
  bool loadNewMaze(int, int, int, algorithm_type);
  bool solveMaze(solving_type);
};

#endif /* _MAZE_HH_ */
