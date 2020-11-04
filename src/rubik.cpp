#include "rubik.hpp"

static std::string	gen(int n)
{
	char	s[] = "DRLUFB";
	std::string	ret("");

	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		ret += s[rand() % 6];
		if (rand() % 100 >= 50)
			ret += "2";
		if (rand() % 100 >= 50)
			ret += "'";
	}
	std::cout << "generated instructions: " << ret << std::endl;
	return ret;
}

int		main(int ac, char **av)
{
	Cube	cube;
	Parser	parser;
	Solver	solver;
	int		gen_nb;

	if (ac < 2)
	{
		std::cout << "usage: ./rubik \"instructions\"" << std::endl;
		return 0;
	}
	if (ac == 2)
		parser.Parse(av[1], cube);
	else
	{
		gen_nb = atoi(av[2]);
		if (gen_nb == 0)
		{
			std::cout << "second parameter can't be 0 !" << std::endl;
			return 0;
		}
		parser.Parse(gen(gen_nb).c_str(), cube);
	}
	cube.print_cube();
	solver.solve(cube);
	std::cout << "\n====================\n" << std::endl;
	cube.print_cube();
	cube.print_moves();
	return 0;
}