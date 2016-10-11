/* Gregoire DUCHARME */
/* 06/08/2016 */

#ifndef _PARSER_HH_
# define _PARSER_HH_

# include <iostream>
# include <fstream>
# include <cstring>

# include "Maze.hh"

/* Flag used to defined the parameter of the binary file */
const char ARG_LOAD_BINARY[] = "--lb";
const char ARG_SAVE_BINARY[] = "--sb";
const char ARG_SAVE_SVG[] = "--sv";
const char ARG_SEED[] = "--g";

class Parser {
  bool load_bin;
  bool new_maze;
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

public:
  Parser(int ac, char **argv);
  bool isValid() const;
  bool run();
};

#endif
