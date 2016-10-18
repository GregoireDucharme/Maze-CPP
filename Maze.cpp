/* Gregoire DUCHARME */
/* 03/08/2016 */

#include "Maze.hh"

/* check if Cell is not and edge */
bool	Maze::checkCell(Cell cell)
{
  int xA, xB, yA, yB;
  for (unsigned int i = 0; i < _countEdges; i++) {
    if (_edges[i].getxA() < _edges[i].getxB()) {
      xA = _edges[i].getxA();
      xB = _edges[i].getxB();
    }
    else {
      xA = _edges[i].getxB();
      xB = _edges[i].getxA();
    }
    if (_edges[i].getyA() < _edges[i].getyB()) {
      yA = _edges[i].getyA();
      yB = _edges[i].getxB();
    }
    else {
      yA = _edges[i].getyB();
      yB = _edges[i].getxA();
    }
    if (xA <= cell.getX() && xB >= cell.getX() &&
	yA <= cell.getY() && yB >= cell.getY())
      return false;
  }
  return true;
}

bool	Maze::getCells(std::vector<Cell> &cells, Cell current)
{
  int index = 0;
  int deepness = current.getDeepness() + 1;
  if (current.getX() > 0) {
    if (checkCell(Cell(current.getX() - 1, current.getY())))
      cells.push_back(Cell(current.getX() - 1, current.getY(), index++, deepness));
  }
  if (current.getX() < _width) {
    if (checkCell(Cell(current.getX() + 1, current.getY())))
      cells.push_back(Cell(current.getX() + 1, current.getY(), index++, deepness));
  }
  if (current.getY() > 0) {
    if (checkCell(Cell(current.getX(), current.getY() - 1)))
      cells.push_back(Cell(current.getX(), current.getY() - 1, index++, deepness));
  }
  if (current.getY() < _height) {
    if (checkCell(Cell(current.getX(), current.getY() + 1)))
      cells.push_back(Cell(current.getX(), current.getY() + 1, index++, deepness));
  }
  if (cells.size() == 0)
    return false;
  return true;
}

bool	Maze::solvePM()
{
  return false;
}

bool	Maze::solvePE()
{
  return false;
}

bool	Maze::solvePB()
{
  return false;
}

bool	Maze::solvePD()
{
  std::vector<Cell> path;
  std::vector<std::vector<Cell>> cells;
  int i = 0, j = -1;
  bool check = true;
  unsigned int index;
  path.push_back(Cell());
  while (1) {
    if (check) {
      cells.push_back(std::vector<Cell>());
      getCells(cells[++j], path[i]);
    }
    if (cells[j].size() > 0) {
      path.push_back(cells[j][0]);
      check = true;
    }
    else {
      index = path[i].getIndex() + 1;
      path.pop_back();
      i--;
      j--;
      if (cells[j].size() > index)
	path.push_back(cells[j][index]);
      check = false;
    }
    if (j == -1)
      return false;
    if (path[i].getX() == _width && path[i].getY() == _height)
      return true;
    i++;
  }
  return false;
}

/* Dispatch solving methog depending on solving type */
bool	Maze::solveMaze(solving_type solving)
{
  switch (solving) {
  case PM:
    return solvePM();
    break;
  case PE:
    return solvePE();
    break;
  case PB:
    return solvePB();
    break;
  case PD:
    return solvePD();
    break;
  default:
    return false;
    break;
  }
}

/* Check if the 2D map of the maze still contains unexplored parts */
bool	Maze::checkMap(std::vector<std::vector<int>> map) const
{
  int x = 0, y = 0;

  while (y < _height) {
    x = 0;
    while (x < _width) {
      if (map[x][y] == false) {
	return false;
      }
      x++;
    }
    y++;
  }
  return true;
}

/* Initialize the values of the maze class and check potential error */
bool	Maze::initValues(int width, int height, unsigned int countEdges)
{
  _width = width;
  _height = height;
  _countEdges = countEdges;
  if (!_width || !_height) {
    std::cerr << "Wrong size for new maze" << std::endl;
    return false;
  }
  return true;
}

void	Maze::createEdgeEller(int y, bool way, std::vector<std::vector<int>> map)
{
  int x = 0;

  if (way == HORIZONTAL) {
    int value = map[x][y];
    /* Line to process */
    while (x < _width) {
      if (map[x][y] != value) {
	value = map[x][y];
	_countEdges++;
	_edges.push_back(Edge(x, y, x, y + 1));
      }
      if (y > 0 && map[x][y] != map[x][y - 1]) {
	_countEdges++;
	_edges.push_back(Edge(x, y, x + 1, y));
      }
      x++;
    }
  }
  else /* way == VERTICAL */ {
    /*Column to process  */
    while (x < _width) {
      
      if (map[x][y] == 0) {
	_countEdges++;
	_edges.push_back(Edge(x, y, x + 1, y));
      }
      x++;
    }
  }
}

/* Filling the 2D map and instanciating the edges */
void	Maze::fillMapEller(std::vector<std::vector<int>> map,
			   std::mt19937 generator)
{
  int	x = 0, y = 0, val = 0, previousValue = 0, minValue = 0;
  bool	check = false;

  while (y < _height) {
    /* Init each cell to a value */
    x = 0;
    checkMap(map);
    minValue = val;
    while (x < _width) {
      if (!map[x][y])
	map[x][y] = ++val;
      x++;
    }
    checkMap(map);
    /* Merge randomly cells */
    x = 1;
    while (x < _width) {
      if (generator() % 2 == 0) {
	if (map[x][y] > minValue)
	  map[x][y] = map[x - 1][y];
	else { /* Merging a cell already set */
	  previousValue = map[x - 1][y];
	  for (int tmpX = x - 1; tmpX >= 0 && map[tmpX][y] == previousValue ; tmpX--) {
	    map[tmpX][y] = map[x][y];
	  }
	}
      }
      x++;
    }
    checkMap(map);
    createEdgeEller(y, HORIZONTAL, map);
    y++;
    check = false;
    /* Add vertical connexion*/
    if (y < _height) {
      while (!check) {
	x = 0;
	while (x < _width) {
	  if ((x == 0 || map[x - 1][y] != map[x][y - 1]) &&
	      generator() % 2 == 0) {
	    map[x][y] = map[x][y - 1];
	  }
	  x++;
	}
	x = 0;
	check = false;
	previousValue = map[x][y - 1];
	while (x < _width) {
	  if (map[x][y] == previousValue)
	    check = true;
	  if (map[x][y - 1] != previousValue && check == false)
	    break;
	  else if (map[x][y - 1] != previousValue && check == true)
	    {
	      previousValue = map[x][y - 1];
	      if (x + 1 < _width)
		check = false;
	    }
	  else
	    x++;
	}
	checkMap(map);
      }
      createEdgeEller(y, VERTICAL, map);
    }
  }
}
void	Maze::fillMapAldousBroder(std::vector<std::vector<int>> map,
				  std::mt19937 generator)				
{
  int x = 0, y = 0, previousX, previousY, way;
  map[x][y] = true;
  while (!checkMap(map)) {
    previousX = x;
    previousY = y;
    way = generator() % 4;
    switch (way) {
    case LEFT:
      if (x > 0)
	x--;
      break;
    case RIGHT:
      if (x < _width - 1)
	x++;
      break;
    case UP:
      if (y > 0)
	y--;
      break;
    case DOWN:
      if (y < _height - 1)
	y++;
      break;
    }
    if (map[x][y] == false) {
      _countEdges++;
      _edges.push_back(Edge(previousX, previousY, x, y));
      map[x][y] = true;
    }
  }
}

/* If no maze to load is specified then create a new one */
bool	Maze::loadNewMaze(int seed, int width, int height, algorithm_type type)
{
  if (initValues(width, height) == false) {
    return false;
  }
  std::vector<std::vector<int>> map;
  map.resize(_width);
  int x = 0, y = 0;
  while (x < _width) {
    y = 0;
    map[x].resize(_height);
    while (y < _height) {
      map[x][y] = 0;
      y++;
    }
    x++;
  }
  std::mt19937 generator(seed);
  switch (type)
    {
    case ALDOUS_BRODER:
      fillMapAldousBroder(map, generator);
      break;
    case ELLER:
      fillMapEller(map, generator);
      break;
    }
  return true;
}

bool	Maze::loadFromBinaryFile(std::string filename) 
{
  std::ifstream	file(filename);
  int		val;
  std::vector<int>  bytes;

  if (file.is_open())
    {
      while (file.read((char*)&val, sizeof(int))) {
        bytes.push_back(val);
      }
      if ((bytes.size() + 1) % 4 != 0) {
	std::cerr << "File length incorrect" << std::endl;
	return false;
      }
    }
  else {
    std::cerr << "Couldn't open file" << std::endl;
    return false;
  }
  file.close();
  if (initValues(bytes[0], bytes[1], bytes[2]) == false) {
    return false;
  }
  for(unsigned int i = 3; i < bytes.size(); i += 4) {
    _edges.push_back(Edge(bytes[i], bytes[i+1], bytes[i+2], bytes[i+3]));
  }
  if (_countEdges != _edges.size()) {
    std::cerr << "Binary file incorrect" << std::endl;
  }
  return true;
}

bool	Maze::saveToBinaryFile(std::string filename) const
{
  std::ofstream	file;

  file.open(filename.c_str());
  if (file.is_open()) {
    file.write((char*)&_width, sizeof(int));
    file.write((char*)&_height, sizeof(int));
    file.write((char*)&_countEdges, sizeof(int));
    int xA, yA, xB, yB;
    for (unsigned int i = 0; i < _edges.size(); i++) {
      xA = _edges[i].getxA();
      yA = _edges[i].getyA();
      xB = _edges[i].getxB();
      yB = _edges[i].getyB();
      file.write((char*)&xA, sizeof(int));
      file.write((char*)&yA, sizeof(int));
      file.write((char*)&xB, sizeof(int));
      file.write((char*)&yB, sizeof(int));
    }
    file.close();
    return true;
  }
  std::cerr << "Couldn't open file" << std::endl;
  return false;
}

bool	Maze::saveToSvgFile(std::string filename) const
{
  std::ofstream	file;

  file.open(filename.c_str());
  if (file.is_open()) {
    file << "<svg width=\""<< _width * SIZE_RATIO;
    file <<"\" height=\""<< _height * SIZE_RATIO;
    file << "\" xmlns=\"http://www.w3.org/2000/svg\">" << std::endl;
    file << "<rect width=\""<< _width * SIZE_RATIO;
    file << "\" height=\"" << _height * SIZE_RATIO;
    file << "\" style=\"fill:black\" />" << std::endl;
    for (unsigned int i = 0; i < _edges.size(); i++)
      {
	file << _edges[i] << std::endl;
      }
    file << "</svg>" << std::endl;
    file.close();
    return true;
  }
  std::cerr << "Couldn't open file" << std::endl;
  return false;
}

/* Checking value from the maze class */
bool	Maze::isValid() const
{
  if (!_width || !_height || !_countEdges) {
    return false;
  }
  return true;
}
