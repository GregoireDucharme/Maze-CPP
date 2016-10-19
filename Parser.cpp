/* Gregoire DUCHARME */
/* 06/08/2016 */

#include "Parser.hh"

/* Check if the string is only numeric char */
bool	Parser::isNumeric(char *str) const
{
  for (unsigned int i; i < strlen(str); i++) {
    if (str[i] < '0' || str[i] > '9')
      return false;
  }
  return true;
}


void	Parser::initGenerationAlgorithm(char *argv)
{
  if (!ARG_G_SEED.compare(argv))
    new_maze = true;
  else if (!ARG_GA_SEED.compare(argv))
    new_maze_ga = true;
  else if (!ARG_GE_SEED.compare(argv))
    new_maze_ge = true;
}

void	Parser::checkSolvingFlag(char *argv)
{
  if (!ARG_SOLVE_PM.compare(argv)) {
    solving = Maze::PM;
  }
  else if (!ARG_SOLVE_PE.compare(argv)) {
    solving = Maze::PE;
  }
  else if (!ARG_SOLVE_PB.compare(argv)) {
    solving = Maze::PB;
  }
  else if (!ARG_SOLVE_PD.compare(argv)) {
    solving = Maze::PD;
  }
}

/* Only constructor of the Parser class */
/* Usage de const char defined in Parser.hh */
Parser::Parser(int ac, char **argv)
{
  load_bin = false;
  new_maze = false;
  new_maze_ga = false;
  new_maze_ge = false;
  save_bin = false;
  save_svg = false;
  seed = 0;
  width = 0;
  height = 0;
  solving = Maze::NONE;
  for (int i = 0; i < ac; i++) {
    if (!ARG_LOAD_BINARY.compare(argv[i]) && ac > i + 1) {
      load_bin = true;
      load_bin_file = argv[i + 1];
    }
    else if (!ARG_SAVE_BINARY.compare(argv[i]) && ac > i + 1) {
      save_bin = true;
      save_bin_file = argv[i + 1];
    }
    else if (!ARG_SAVE_SVG.compare(argv[i]) && ac > i + 1) {
      save_svg = true;
      save_svg_file = argv[i + 1];
    }
    else if ((!ARG_G_SEED.compare(argv[i]) ||
	      !ARG_GA_SEED.compare(argv[i]) ||
	      !ARG_GE_SEED.compare(argv[i])) &&
	     ac > i + 2) {
      if (ac > i + 3 && isNumeric(argv[i + 1]) &&
	  isNumeric(argv[i + 2]) &&
	  isNumeric(argv[i + 3])) {
	seed = std::stoi(argv[i + 1]);
	width = std::stoi(argv[i + 2]);
	height = std::stoi(argv[i + 3]);
	initGenerationAlgorithm(argv[i]);
      }
      else if (isNumeric(argv[i + 1]) &&
	       isNumeric(argv[i + 2])) {
	seed = time(0);
	width = std::stoi(argv[i + 1]);
	height = std::stoi(argv[i + 2]);
	initGenerationAlgorithm(argv[i]);
      }
    }
    checkSolvingFlag(argv[i]);
  }
}

bool Parser::isValid() const
{
  return true;
}

bool	Parser::dispatchNewMaze()
{
  std::cout << "Generating new maze with seed "<<  seed << std ::endl;
  if (new_maze || new_maze_ga)
    return (maze.loadNewMaze(seed, width, height, Maze::ALDOUS_BRODER));
  else if (new_maze_ge)
    return(maze.loadNewMaze(seed, width, height, Maze::ELLER));
  return false;
}

bool	Parser::run()
{
  // Check if parameter are correct
  if (load_bin && !new_maze && !new_maze_ga && !new_maze_ge) {
    std::cout << "Loading binary file "<<  load_bin_file << std ::endl;
    if (!maze.loadFromBinaryFile(load_bin_file)) {
      std::cerr << "Could not load from binary file " << load_bin_file << std::endl;
      return false;
    }
  }
  else if (((new_maze && !new_maze_ga && !new_maze_ge) ||
	    (!new_maze && new_maze_ga && !new_maze_ge) ||
	    (!new_maze && !new_maze_ga && new_maze_ge)) &&
	   !load_bin) {
    if (!dispatchNewMaze()) {
      std::cerr << "Could not generate new file " << load_bin_file << std::endl;
      return false;
    }
  }
  else {
    std::cerr << "Error, maze not specified" << std::endl;
    std::cerr << "Use "<< ARG_G_SEED << " to generate one" << std::endl;
    std::cerr << "Or use "<< ARG_GE_SEED << " to generate one" << std::endl;
    std::cerr << "Or use "<< ARG_GA_SEED << " to generate one" << std::endl;
    std::cerr << "Or " << ARG_LOAD_BINARY <<" to load from binary file" << std::endl;
    return false;
  }
  if (maze.isValid()) {
    if (save_bin) {
      std::cout << "Saving binary file"<<  save_bin_file << std ::endl;
      if (!maze.saveToBinaryFile(save_bin_file)) {
	std::cerr << "Could not save to binary file " << save_svg_file << std::endl;
      }
    }
    if (save_svg) {
      std::cout << "Saving svg file "<<  save_svg_file << std ::endl;
      if (!maze.saveToSvgFile(save_svg_file)) {
	std::cerr << "Could not save to svg file " << save_svg_file << std::endl;
      }
    }
    if (solving != Maze::NONE) {
      auto start = std::chrono::steady_clock::now();
      if (maze.solveMaze(solving)) {
	auto end = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast
	  <std::chrono::milliseconds>(end - start);
	std::cout << "Maze solved in "<< duration.count() << "ms" << std::endl;
      }
      else {
	std::cerr << "Error, could not solve given maze" << std::endl;
      }
    }
  }
  else {
    std::cerr << "Invalid maze" <<std::endl;
    return false;
  }
  return true;
}
