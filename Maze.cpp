/* Gregoire DUCHARME */
/* Yixuan Zhang */
/* 23/10/2016 */

#include "Maze.hh"

/* check if Cell is not and edge */
bool	Maze::checkCell(Cell cell)
{
  int xA, xB, yA, yB;
  /* Get the minimum value for each position so that the "if" condition is easier */
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
      yB = _edges[i].getyB();
    }
    else {
      yA = _edges[i].getyB();
      yB = _edges[i].getyA();
    }
    if (xA * 2 <= cell.getX() && xB * 2 >= cell.getX() &&
	yA * 2 <= cell.getY() && yB * 2 >= cell.getY())
      return false;
  }
  return true;
}

bool	Maze::getCells(std::vector<Cell> &cells, std::vector<Cell> path)
{
  int index = 0;
  int deepness = path.back().getDeepness() + 1;
  Cell tmp;

  /* Check if the surrounding cells are walls and have been visited in the current path */
  if (path.back().getX() > 0) {
    tmp = Cell(path.back().getX() - 1, path.back().getY(), index, deepness);
    if (tmp.isNotIn(path) && checkCell(tmp)) {
      tmp.setIndex(index++);
      cells.push_back(tmp);
    }
  }
  if (path.back().getX() < _width * 2 - 1) {
    tmp = Cell(path.back().getX() + 1, path.back().getY(), index, deepness);
    if (tmp.isNotIn(path) && checkCell(tmp)) {
      tmp.setIndex(index++);
      cells.push_back(tmp);
    }
  }
  if (path.back().getY() > 0) {
    tmp = Cell(path.back().getX(), path.back().getY() - 1, index, deepness);
    if (tmp.isNotIn(path) && checkCell(tmp)) {
      tmp.setIndex(index++);    
      cells.push_back(tmp);
    }
  }
  if (path.back().getY() < _height * 2 - 1) {
    tmp = Cell(path.back().getX(), path.back().getY() + 1, index, deepness);
    if (tmp.isNotIn(path) && checkCell(tmp)) {
      tmp.setIndex(index++);     
      cells.push_back(tmp);
    }
  }
  /* Dead end */
  if (cells.size() == 0)
    return false;
  return true;
}

/* Copy the maze svg file and add the solution in red line  */
void	Maze::saveSolvedToSvg(std::vector<Cell> path)
{
  std::ifstream file;
  std::ofstream file_solved;
  std::string line;

  file.open(_filename.c_str());
  file_solved.open("solved_" + _filename);
  if (file.is_open() && file_solved.is_open()) {
    while (getline(file, line)) {
      if (line.compare("</svg>"))
	file_solved << line << std::endl;
    }
    for (unsigned int i; i + 1 < path.size(); i++) {
      file_solved << &path[i] << std::endl;
    }
    file_solved << "</svg>" << std::endl;
    file_solved.close();
    file.close();
  }
}

bool	Maze::solvePM()
{
  return solvePB();
}

bool	Maze::solvePE()
{
  return solvePB();
}

/* Solving breadth first */
bool	Maze::solvePB()
{
  std::vector<std::vector<Cell>> pathes;
  std::vector<std::vector<Cell>> cells;
  std::vector<Cell> tmp, tmp_to_push;
  unsigned int i = 0, k = 0;
  int j = -1;
  bool check = true;

  pathes.push_back(std::vector<Cell>());
  pathes.back().push_back(Cell(1, 1));
  while (check) {
    check = false;
    i = 0;
    /* Checking possible path for each path instanciated */
    while (i < pathes.size()) {
      cells.push_back(std::vector<Cell>());
      getCells(cells[++j], pathes[i]);
      k = 0;
      tmp = pathes[i];
      /* Then instanciated all possible path */
      while (k < cells[j].size()) {
	tmp_to_push = tmp;
	if (k == 0)
	  pathes[i].push_back(cells[j][k]);
	else {
	  tmp_to_push.push_back(cells[j][k]);
	  pathes.push_back(tmp_to_push);
	}
	/* Bottom right corner */
	if (cells[j][k].getX() == _width * 2 - 1 &&
	    cells[j][k].getY() == _height * 2 - 1) {
	  if (_filename.compare("")) {
	    tmp.push_back(cells[j][k]);
	    saveSolvedToSvg(tmp);
	  }
	  return true;

	}
	check = true;
	k++;
      }
      i++;
    }
  }
  return false;
}

/* Solving depth first */
bool	Maze::solvePD()
{
  std::vector<Cell> path;
  std::vector<std::vector<Cell>> cells;
  int i = 0, j = -1;
  bool check = true;
  unsigned int index = 0;
  path.push_back(Cell(1, 1));
  /* infinite loop */
  /* Stop if all path have been explored and couldn't reach to bottom right corner */
  while (1) {
    /* Check the cells around current position */
    if (check) {
      cells.push_back(std::vector<Cell>());
      getCells(cells[++j], path);
      index = 0;
    }
    if (cells[j].size() > index) {
      path.push_back(cells[j][index]);
      check = true;
      i++;
    }
    else if (i >= 0) {
      index = path[i--].getIndex() + 1;
      cells.pop_back();
      j--;
      path.pop_back();
      check = false;
    }
    else
      return false;
    /* Bottom right corner */
    if (path.back().getX() == _width * 2 - 1 && path.back().getY() == _height * 2 - 1) {
      if (_filename.compare("")) {
	saveSolvedToSvg(path);
      }
      return true;
    }
    if (j == -1 || i == -1)
      return false;
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
  int x = generator() % _width, y = generator() % _height, previousX, previousY, way;
  map[x][y] = true;
  while (!checkMap(map)) {
    previousX = x;
    previousY = y;
    way = generator() % 4;
    /* Randomize the way to explore */
    switch (way) {
    case LEFT:
      if (x > 0)
	x--;
      break;
    case RIGHT:
      if (x < _width)
	x++;
      break;
    case UP:
      if (y > 0)
	y--;
      break;
    case DOWN:
      if (y < _height)
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
  map.resize(_width + 1);
  int x = 0, y = 0;
  while (x <= _width) {
    y = 0;
    map[x].resize(_height + 1);
    while (y <= _height) {
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

bool	Maze::saveToSvgFile(std::string filename)
{
  std::ofstream	file;

  file.open(filename.c_str());
  if (file.is_open()) {
    file << "<svg width=\""<< _width * SIZE_RATIO;
    file <<"\" height=\""<< _height * SIZE_RATIO;
    file << "\" xmlns=\"http://www.w3.org/2000/svg\">" << std::endl;
    file << "<rect x=\"0\" y =\"0\" width=\""<< _width * SIZE_RATIO;
    file << "\" height=\"" << _height * SIZE_RATIO;
    file << "\" style=\"fill:black\" />" << std::endl;
    for (unsigned int i = 0; i < _edges.size(); i++)
      {
	/* Operator oveload */
	file << _edges[i] << std::endl;
      }
    file << "</svg>" << std::endl;
    file.close();
    _filename = filename;
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
