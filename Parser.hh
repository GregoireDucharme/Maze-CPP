/* Gregoire DUCHARME */
/* 06/08/2016 */

#ifndef _PARSER_HH_
# define _PARSER_HH_

# include <iostream>
# include <fstream>
# include <cstring>

# include "Maze.hh"

/* Flag used to defined the parameter of the binary file */

const std::string ARG_LOAD_BINARY = "--lb";
const std::string ARG_SAVE_BINARY = "--sb";
const std::string ARG_SAVE_SVG = "--sv";

const std::string ARG_G_SEED = "--g";
const std::string ARG_GA_SEED = "--ga";
const std::string ARG_GE_SEED = "--ge";

const std::string ARG_SOLVE_PM = "--pm";
const std::string ARG_SOLVE_PE = "--pe";
const std::string ARG_SOLVE_PB = "--pb";
const std::string ARG_SOLVE_PD = "--pd";

class Parser {
  bool load_bin;
  int new_maze;
  int new_maze_ga;
  int new_maze_ge;
  bool save_bin;
  bool save_svg;
  std::string load_bin_file;
  std::string save_bin_file;
  std::string save_svg_file;
  int seed;
  int width;
  int height;
  Maze maze;
  bool isNumeric(char*) const;
  bool dispatchNewMaze();

public:
  Parser(int ac, char **argv);
  bool isValid() const;
  bool run();
};

#endif
