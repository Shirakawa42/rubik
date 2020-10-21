#pragma once

#include "Cube.hpp"

class Parser
{
	public:
		Parser();
		~Parser();
		void	Parse(char const *str, Cube & cube);
};