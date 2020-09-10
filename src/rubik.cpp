#include "rubik.hpp"

int		main(int ac, char **av)
{
	Cube	cube;
	Parser	parser;

	if (ac < 2)
	{
		std::cout << "usage: ./rubik \"trucs\"" << std::endl;
		return 0;
	}
	parser.Parse(av[1], cube);
	cube.print_cube();
	
	return 0;
}