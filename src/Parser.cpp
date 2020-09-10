#include "Parser.hpp"

Parser::Parser()
{

}

Parser::~Parser()
{

}

static std::string	removeWrong(std::string str)
{
	std::string		ret;
	std::string		ok = "RLUDFB'2";

	for (int i = 0; i < str.length(); i++)
	{
		if (ok.find(str[i]) != std::string::npos)
			ret += str[i];
	}
	return ret;
}

void	Parser::Parse(char *str, Cube & cube)
{
	std::string	s = std::string(str);
	std::string		ok = "RLUDFB";
	char			letter;
	int				nb_rota;
	bool			prime;

	s = removeWrong(s);
	for (int i = 0; i < s.length();)
	{
		nb_rota = 1;
		prime = false;
		while (ok.find(s[i]) == std::string::npos)
			i++;
		if (i >= s.length())
			break ;
		if (ok.find(s[i]) != std::string::npos)
			letter = s[i++];
		if (s[i] == '\'')
		{
			prime = true;
			i++;
		}
		if (s[i] == '2')
		{
			nb_rota = 2;
			i++;
		}
		if (s[i] == '\'')
		{
			prime = true;
			i++;
		}
		cube.move(letter, prime, nb_rota);
	}
}