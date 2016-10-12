/* Gregoire DUCHARME */
/* 03/08/2016 */

#include "Maze.hh"

/* Check if the 2D map of the maze still contains unexplored parts */
bool	Maze::checkMap(std::vector<std::vector<bool>> map) const
{
  int x = 0, y = 0;

  while (x < _width) {
    y = 0;
    while (y < _height) {
      if (map[x][y] == false) {
	return false;
      }
      y++;
    }
    x++;
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

/* Filling the 2D map and instanciating the edges */
void	Maze::fillMapEller(std::vector<std::vector<bool>> map,
				  std::mt19937 generator,
				  int x, int y)
{
  (void)map;
  (void)generator;
  (void)x;
  (void)y;
}
void	Maze::fillMapAldousBroder(std::vector<std::vector<bool>> map,
				  std::mt19937 generator,
				  int x, int y)
{
  int previousX, previousY, way;
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
  std::vector<std::vector<bool>> map;
  map.resize(_width);
  int x = 0, y = 0;
  while (x < _width) {
    y = 0;
    map[x].resize(_height);
    while (y < _height) {
      map[x][y] = false;
      y++;
    }
    x++;
    }
  std::mt19937 generator(seed);
  x = generator() % _width;
  y = generator() % _height;
  switch (type)
    {
    case ALDOUS_BRODER:
      fillMapAldousBroder(map, generator, x, y);
      break;
    case ELLER:
      fillMapAldousBroder(map, generator, x, y);
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
