#include "Cube.hpp"

Cube::Cube()
{
	char current = '0';

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				cube_array[i][j][k] = current;
		current++;
	}
}

Cube::~Cube()
{

}

void	Cube::print_colored_char(char c)
{
	if (c == '0')
		printf("\x1B[33m0\033[0m");
	else if (c == '1')
		printf("\x1B[37m1\033[0m");
	else if (c == '2')
		printf("\x1B[96m2\033[0m");
	else if (c == '3')
		printf("\x1B[93m3\033[0m");
	else if (c == '4')
		printf("\x1B[92m4\033[0m");
	else if (c == '5')
		printf("\x1B[91m5\033[0m");
}

void	Cube::print_cube()
{
	for (int i = 0; i < 3; i++)
	{
		std::cout << "    ";
		for (int j = 0; j < 3; j++)
			print_colored_char(cube_array[0][i][j]);
		std::cout << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 1; j < 5; j++)
		{
			for (int k = 0; k < 3; k++)
				print_colored_char(cube_array[j][i][k]);
			std::cout << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < 3; i++)
	{
		std::cout << "    ";
		for (int j = 0; j < 3; j++)
			print_colored_char(cube_array[5][i][j]);
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
}