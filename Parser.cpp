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

  for (int i = 0; i < ac; i++) {
    if (ARG_LOAD_BINARY.compare(argv[i]) && ac > i + 1) {
      load_bin = true;
      load_bin_file = argv[i + 1];
    }
    else if (ARG_SAVE_BINARY.compare(argv[i]) && ac > i + 1) {
      save_bin = true;
      save_bin_file = argv[i + 1];
    }
    else if (ARG_SAVE_SVG.compare(argv[i]) && ac > i + 1) {
      save_svg = true;
      save_svg_file = argv[i + 1];
    }
    else if ((!(new_maze = ARG_G_SEED.compare(argv[i])) ||
	      !(new_maze_ga = ARG_GA_SEED.compare(argv[i])) ||
	      !(new_maze_ge = ARG_GE_SEED.compare(argv[i]))) &&
	     ac > i + 2) {
      if (ac > i + 3 && isNumeric(argv[i + 1]) &&
	  isNumeric(argv[i + 2]) &&
	  isNumeric(argv[i + 3])) {
	seed = std::stoi(argv[i + 1]);
	width = std::stoi(argv[i + 2]);
	height = std::stoi(argv[i + 3]);
      }
      else {
	seed = time(0);
	width = std::stoi(argv[i + 1]);
	height = std::stoi(argv[i + 2]);
      }
    }
  }
}

bool Parser::isValid() const
{
  return true;
}

bool	Parser::dispatchNewMaze()
{
  std::cout << "Generating new maze with seed "<<  seed << std ::endl;
  if (!new_maze)
    return (maze.loadNewMaze(seed, width, height));
  else if (!new_maze_ge)
    return (maze.loadNewMaze(seed, width, height));
  else if (!new_maze_ga)
    return(maze.loadNewMaze(seed, width, height));
  return false;
}

bool	Parser::run()
{
  // Check if parameter are correct
  if (load_bin && new_maze && new_maze_ga && new_maze_ge) {
    std::cout << "Loading binary file "<<  load_bin_file << std ::endl;
    if (!maze.loadFromBinaryFile(load_bin_file)) {
      std::cerr << "Could not load from binary file " << load_bin_file << std::endl;
      return false;
    }
  }
  else if (((!new_maze && new_maze_ga && new_maze_ge) ||
	    (new_maze && !new_maze_ga && new_maze_ge) ||
	    (new_maze && new_maze_ga && !new_maze_ge)) &&
	   !load_bin) {
    if (!dispatchNewMaze()) {
      std::cerr << "Could not generate new file " << load_bin_file << std::endl;
      return false;
    }
  }
  else {
    std::cerr << "Error, maze not specified" << std::endl;
    std::cerr << "Use "<< ARG_G_SEED << " to generate one";
    std::cerr << "Or use "<< ARG_GE_SEED << " to generate one";
    std::cerr << "Or use "<< ARG_GA_SEED << " to generate one";
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
      std::cout << "Saving svg file"<<  save_svg_file << std ::endl;
      if (!maze.saveToSvgFile(save_svg_file)) {
	std::cerr << "Could not save to svg file " << save_svg_file << std::endl;
      }
    }
  }
  else {
    std::cerr << "Invalid maze" <<std::endl;
    return false;
  }
  return true;
}
