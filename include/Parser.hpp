#pragma once

#include "Cube.hpp"

class Parser
{
	public:
		Parser();
		~Parser();
		void	Parse(char *str, Cube & cube);
};