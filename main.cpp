/* Gregoire DUCHARME */
/* 02/08/2016 */

#include "Parser.hh"

int	main(int ac, char **argv)
{
  Parser	parser(ac, argv);

  /* End of the funnel of return, if false is returned then errors message is displayed */
  if (parser.isValid()) {
    if (!parser.run()) {
      std::cerr << "An error occured" << std::endl;
    };
  }
  else {
    std::cout << "./mazer -- lb filename.maze -- sv filename.svg";
    std::cout << "#load binary file and save svg file" << std::endl;
    std::cout << "./mazer -- g seed -- sb filename.maze";
    std::cout << "#generate with seed value, save binary file" << std::endl;
    std::cout << "./mazer -- g seed -- sv filename.svg";
    std::cout << "#generate with seed value, save svg file" << std::endl;
    std::cout << "./mazer -- g seed -- sb filename.maze -- sv filename.svg";
    std::cout << "#gen with seed, save binary, save svg" << std::endl;
    std::cout << "./mazer -- ga … " << std::endl;
    std::cout << "# generate a maze using the Aldous-Broder method" << std::endl;
    std::cout << "./mazer -- ge … " << std::endl;
    std::cout << "# generate a maze using the Eller’s algorithm." << std::endl;
    std::cout << "./mazer -- pm … " << std::endl;
    std::cout << "# solve the maze using Dijkstra’s algorithm with";
    std::cout << "manhattan distance heuristic." << std::endl;
    std::cout << "./mazer -- pe … " << std::endl;
    std::cout << "# solve the maze using Dijkstra’s algorithm ";
    std::cout << "with Euclidean distance heuristic." << std::endl;
    std::cout << "./mazer -- pb … " << std::endl;
    std::cout << "# solve the maze using Breadth First Search" << std::endl;
    std::cout << "./mazer -- pd … " << std::endl;
    std::cout << "#solve the maze using depth first search." << std::endl;
  }
  return 0;
}
