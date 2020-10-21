#include "Cube.hpp"

Cube::Cube()
{
	int current = 0;

	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				cube_array[i][j][k] = current++;
	moves = std::string("");
	nb_moves = 0;
}

Cube::~Cube()
{

}

void	Cube::print_colored_int(int c)
{
	if (c <= 8)
		printf("\x1B[33m0\033[0m");
	else if (c <= 17)
		printf("\x1B[37m1\033[0m");
	else if (c <= 26)
		printf("\x1B[96m2\033[0m");
	else if (c <= 35)
		printf("\x1B[93m3\033[0m");
	else if (c <= 44)
		printf("\x1B[92m4\033[0m");
	else if (c <= 53)
		printf("\x1B[91m5\033[0m");
}

t_move	*Cube::get_moves()
{
	int		l = moves.length();
	t_move	*movelist = new t_move[nb_moves];
	int		current_move = 0;

	for(int i = 0; i < l; i++)
	{
		while((moves[i] < 'A' || moves[i] > 'Z') && i < l)
			i++;
		if (i >= l)
			break ;
		movelist[current_move].letter = moves[i++];
		movelist[current_move].nb = (moves[i] == '2') ? 2 : 1;
		if ((moves[i] == '2' && moves[i+1] == '\'') || moves[i] == '\'')
			movelist[current_move].prime = true;
		else
			movelist[current_move].prime = false;
		movelist[current_move].removed = false;
		movelist[current_move].modified = false;
		current_move++;
	}
	return movelist;
}

void	Cube::read_movelist(t_move *movelist)
{
	reset_moves();
	for (int i = 0; i < nb_moves; i++)
	{
		if (!movelist[i].removed && movelist[i].nb != 0)
		{
			if (movelist[i].nb < 0)
			{
				movelist[i].nb -= (movelist[i].nb*2);
				movelist[i].prime = !movelist[i].prime;
			}
			if (movelist[i].nb > 2)
			{
				while (movelist[i].nb > 4)
					movelist[i].nb -= 4;
				if (movelist[i].nb == 3)
				{
					movelist[i].prime = !movelist[i].prime;
					movelist[i].nb = 1;
				}
			}
			if (movelist[i].nb != 0)
			{
				moves += movelist[i].letter;
				if (movelist[i].nb == 2)
					moves += std::to_string(movelist[i].nb);
				if (movelist[i].prime)
					moves += '\'';
				moves += ' ';
			}
		}
	}
}

bool	Cube::is_move_modified(char letter, char newletter)
{
	if ((letter == 'R' && newletter == 'L')
		|| (letter == 'L' && newletter == 'R')
		|| (letter == 'D' && newletter == 'U')
		|| (letter == 'U' && newletter == 'D')
		|| (letter == 'F' && newletter == 'B')
		|| (letter == 'B' && newletter == 'F'))
		return false;
	return true;
}

void	Cube::reduce_moves()
{
	t_move		*movelist;

	movelist = get_moves();
	for (int i = 0; i < nb_moves; i++)
	{
		while (movelist[i].removed && i < nb_moves)
			i++;
		for (int j = i + 1; j < nb_moves; j++)
		{
			if (movelist[i].letter == movelist[j].letter)
			{
				if (movelist[i].prime == movelist[j].prime)
					movelist[i].nb += movelist[j].nb;
				else
					movelist[i].nb -= movelist[j].nb;
				movelist[j].removed = true;
			}
			else if (is_move_modified(movelist[i].letter, movelist[j].letter))
			{
				movelist[i].modified = true;
				break ;
			}
		}
	}
	read_movelist(movelist);
	delete[](movelist);
}

void	Cube::print_moves()
{
	reduce_moves();
	std::cout << moves << std::endl;
}

void	Cube::reset_moves()
{
	moves = std::string("");
}

void	Cube::print_cube()
{
	for (int i = 0; i < 3; i++)
	{
		std::cout << "    ";
		for (int j = 0; j < 3; j++)
			print_colored_int(cube_array[0][i][j]);
		std::cout << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 1; j < 5; j++)
		{
			for (int k = 0; k < 3; k++)
				print_colored_int(cube_array[j][i][k]);
			std::cout << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < 3; i++)
	{
		std::cout << "    ";
		for (int j = 0; j < 3; j++)
			print_colored_int(cube_array[5][i][j]);
		std::cout << std::endl;
	}
}

void	Cube::horizontal_swap(int i1, int j1, int i2, int j2)
{
	char	tmp;

	for (int i = 0; i < 3; i++)
	{
		tmp = cube_array[i1][j1][i];
		cube_array[i1][j1][i] = cube_array[i2][j2][i];
		cube_array[i2][j2][i] = tmp;
	}
}

void	Cube::vertical_swap(int j, bool prime)
{
	char	tmp[3];
	char	tmp2[3];
	int		k = (j == 2) ? 0 : 2;

	if (!prime)
	{
		tmp[0] = cube_array[2][0][j];
		tmp[1] = cube_array[2][1][j];
		tmp[2] = cube_array[2][2][j];
		cube_array[2][0][j] = cube_array[0][0][j];
		cube_array[2][1][j] = cube_array[0][1][j];
		cube_array[2][2][j] = cube_array[0][2][j];
		tmp2[0] = cube_array[5][0][j];
		tmp2[1] = cube_array[5][1][j];
		tmp2[2] = cube_array[5][2][j];
		cube_array[5][0][j] = tmp[0];
		cube_array[5][1][j] = tmp[1];
		cube_array[5][2][j] = tmp[2];
		tmp[0] = cube_array[4][0][k];
		tmp[1] = cube_array[4][1][k];
		tmp[2] = cube_array[4][2][k];
		cube_array[4][0][k] = tmp2[2];
		cube_array[4][1][k] = tmp2[1];
		cube_array[4][2][k] = tmp2[0];
		cube_array[0][0][j] = tmp[2];
		cube_array[0][1][j] = tmp[1];
		cube_array[0][2][j] = tmp[0];
	}
	else
	{
		tmp[0] = cube_array[2][0][j];
		tmp[1] = cube_array[2][1][j];
		tmp[2] = cube_array[2][2][j];
		cube_array[2][0][j] = cube_array[5][0][j];
		cube_array[2][1][j] = cube_array[5][1][j];
		cube_array[2][2][j] = cube_array[5][2][j];
		tmp2[0] = cube_array[0][0][j];
		tmp2[1] = cube_array[0][1][j];
		tmp2[2] = cube_array[0][2][j];
		cube_array[0][0][j] = tmp[0];
		cube_array[0][1][j] = tmp[1];
		cube_array[0][2][j] = tmp[2];
		tmp[0] = cube_array[4][0][k];
		tmp[1] = cube_array[4][1][k];
		tmp[2] = cube_array[4][2][k];
		cube_array[4][0][k] = tmp2[2];
		cube_array[4][1][k] = tmp2[1];
		cube_array[4][2][k] = tmp2[0];
		cube_array[5][0][j] = tmp[2];
		cube_array[5][1][j] = tmp[1];
		cube_array[5][2][j] = tmp[0];
	}
}

void	Cube::rotate_swap(int j, bool prime)
{
	int		tmp[3];
	int		tmp2[3];
	int		k = (j == 2) ? 0 : 2;

	if (!prime)
	{
		tmp[0] = cube_array[1][0][j];
		tmp[1] = cube_array[1][1][j];
		tmp[2] = cube_array[1][2][j];
		cube_array[1][0][j] = cube_array[5][k][0];
		cube_array[1][1][j] = cube_array[5][k][1];
		cube_array[1][2][j] = cube_array[5][k][2];
		tmp2[0] = cube_array[0][j][0];
		tmp2[1] = cube_array[0][j][1];
		tmp2[2] = cube_array[0][j][2];
		cube_array[0][j][0] = tmp[2];
		cube_array[0][j][1] = tmp[1];
		cube_array[0][j][2] = tmp[0];
		tmp[0] = cube_array[3][0][k];
		tmp[1] = cube_array[3][1][k];
		tmp[2] = cube_array[3][2][k];
		cube_array[3][0][k] = tmp2[0];
		cube_array[3][1][k] = tmp2[1];
		cube_array[3][2][k] = tmp2[2];
		cube_array[5][k][2] = tmp[0];
		cube_array[5][k][1] = tmp[1];
		cube_array[5][k][0] = tmp[2];
	}
	else
	{
		tmp[0] = cube_array[1][0][j];
		tmp[1] = cube_array[1][1][j];
		tmp[2] = cube_array[1][2][j];
		cube_array[1][0][j] = cube_array[0][j][2];
		cube_array[1][1][j] = cube_array[0][j][1];
		cube_array[1][2][j] = cube_array[0][j][0];
		tmp2[0] = cube_array[5][k][0];
		tmp2[1] = cube_array[5][k][1];
		tmp2[2] = cube_array[5][k][2];
		cube_array[5][k][0] = tmp[0];
		cube_array[5][k][1] = tmp[1];
		cube_array[5][k][2] = tmp[2];
		tmp[0] = cube_array[3][0][k];
		tmp[1] = cube_array[3][1][k];
		tmp[2] = cube_array[3][2][k];
		cube_array[3][0][k] = tmp2[2];
		cube_array[3][1][k] = tmp2[1];
		cube_array[3][2][k] = tmp2[0];
		cube_array[0][j][0] = tmp[0];
		cube_array[0][j][1] = tmp[1];
		cube_array[0][j][2] = tmp[2];
	}
}

void	Cube::rotate_face(int face, bool prime)
{
	char	ret[3][3];

	if (!prime)
	{
    	for (int i = 0; i < 3; ++i) {
    	    for (int j = 0; j < 3; ++j) {
    	        ret[i][j] = cube_array[face][3 - j - 1][i];
    	    }
    	}
    }
    else
    {
		for (int i = 0; i < 3; ++i) {
    	    for (int j = 0; j < 3; ++j) {
    	        ret[i][j] = cube_array[face][j][3 - i - 1];
    	    }
    	}
    }
    for (int i = 0; i < 3; i++)
    	for (int j = 0; j < 3; j++)
    		cube_array[face][i][j] = ret[i][j];
}

void	Cube::movement_U(bool prime, int nb_rota)
{
	for (int i = 0; i < nb_rota; i++)
	{
		if (!prime)
		{
			horizontal_swap(2, 0, 1, 0);
			horizontal_swap(2, 0, 4, 0);
			horizontal_swap(2, 0, 3, 0);
		}
		else
		{
			horizontal_swap(2, 0, 3, 0);
			horizontal_swap(2, 0, 4, 0);
			horizontal_swap(2, 0, 1, 0);
		}
		rotate_face(0, prime);
	}
}

void	Cube::movement_D(bool prime, int nb_rota)
{
	for (int i = 0; i < nb_rota; i++)
	{
		if (prime)
		{
			horizontal_swap(2, 2, 1, 2);
			horizontal_swap(2, 2, 4, 2);
			horizontal_swap(2, 2, 3, 2);
		}
		else
		{
			horizontal_swap(2, 2, 3, 2);
			horizontal_swap(2, 2, 4, 2);
			horizontal_swap(2, 2, 1, 2);
		}
		rotate_face(5, prime);
	}
}

void	Cube::movement_R(bool prime, int nb_rota)
{
	for (int i = 0; i < nb_rota; i++)
	{
		vertical_swap(2, !prime);
		rotate_face(3, prime);
	}
}

void	Cube::movement_L(bool prime, int nb_rota)
{
	for (int i = 0; i < nb_rota; i++)
	{
		vertical_swap(0, prime);
		rotate_face(1, prime);
	}
}

void	Cube::movement_F(bool prime, int nb_rota)
{
	for (int i = 0; i < nb_rota; i++)
	{
		rotate_swap(2, prime);
		rotate_face(2, prime);
	}
}

void	Cube::movement_B(bool prime, int nb_rota)
{
	for (int i = 0; i < nb_rota; i++)
	{
		rotate_swap(0, !prime);
		rotate_face(4, prime);
	}
}

void	Cube::move(char c, bool prime, int nb_rota)
{
	if (c == 'B')
		movement_B(prime, nb_rota);
	else if (c == 'F')
		movement_F(prime, nb_rota);
	else if (c == 'R')
		movement_R(prime, nb_rota);
	else if (c == 'L')
		movement_L(prime, nb_rota);
	else if (c == 'U')
		movement_U(prime, nb_rota);
	else if (c == 'D')
		movement_D(prime, nb_rota);
	moves += c;
	if (nb_rota == 2)
		moves += '2';
	if (prime)
		moves += '\'';
	moves += ' ';
	nb_moves++;
}

bool	Cube::is_face_ok(int face)
{
	for(int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (cube_array[face][i][j] >= 9 * face && cube_array[face][i][j] < 9 * face + 9)
				return false;
	return true;
}

void	Cube::find_value(int val, int & i, int & j, int & k)
{
	for (i = 0; i < 6; i++)
		for (j = 0; j < 3; j++)
			for (k = 0; k < 3; k++)
				if (cube_array[i][j][k] == val)
					return ;
}

int		Cube::get_value(int i, int j, int k)
{
	return cube_array[i][j][k];
}