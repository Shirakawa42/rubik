#pragma once

#include "Cube.hpp"
#include "Parser.hpp"

class Solver
{
	public:
		Solver();
		~Solver();
		void		solve(Cube & cube);
	private:
		Parser		parser;
		std::string	U = std::string("U");
		std::string	D = std::string("D");
		std::string	R = std::string("R");
		std::string	L = std::string("L");
		std::string	F = std::string("F");
		std::string	B = std::string("B");
		void		set_facing(int face);
		void		create_blue_face(Cube & cube);
		void		create_second_line(Cube & cube);
		void		place_arete(Cube & cube, int i, int j, int k, int facing, int value);
		void		place_corner(Cube & cube, int i, int j, int k, int facing, int value);
		void		place_belge(Cube & cube, int i, int j, int k, int facing, int value, int opposite);
};