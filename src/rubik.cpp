#include "rubik.hpp"

int		main(int ac, char **av)
{
	Cube	cube;
	Parser	parser;
	Solver	solver;

	if (ac < 2)
	{
		std::cout << "usage: ./rubik \"trucs\"" << std::endl;
		return 0;
	}
	parser.Parse(av[1], cube);
	cube.print_cube();
	solver.solve(cube);
	std::cout << "\n====================\n" << std::endl;
	cube.print_cube();
	cube.print_moves();
	return 0;
}