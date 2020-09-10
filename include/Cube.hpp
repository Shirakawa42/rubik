#pragma once

#include <iostream>

class Cube
{
	public:
		Cube();
		~Cube();
		void	print_cube();
		void	movement_U(bool prime, int nb_rota);
		void	movement_R(bool prime, int nb_rota);
		void	movement_L(bool prime, int nb_rota);
		void	movement_D(bool prime, int nb_rota);
		void	movement_F(bool prime, int nb_rota);
		void	movement_B(bool prime, int nb_rota);
		void	move(char c, bool prime, int nb_rota);
	private:
		void	horizontal_swap(int i1, int j1, int i2, int j2);
		void	vertical_swap(int j, bool prime);
		void	rotate_face(int i, bool prime);
		void	print_colored_char(char c);
		void	rotate_swap(int j, bool prime);
		char	cube_array[6][3][3];
};