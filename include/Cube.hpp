#pragma once

#include <iostream>
#include <algorithm>

typedef struct	s_move
{
	char	letter;
	bool	prime;
	int		nb;
	bool	removed;
	bool	modified;
}				t_move;

class Cube
{
	public:
		Cube();
		~Cube();
		void		print_cube();
		void		move(char c, bool prime, int nb_rota);
		bool		is_face_ok(int face);
		void		find_value(int val, int & i, int & j, int & k);
		void		print_moves();
		void		reset_moves();
		int			get_value(int i, int j, int k);
	private:
		void		horizontal_swap(int i1, int j1, int i2, int j2);
		void		vertical_swap(int j, bool prime);
		void		rotate_face(int i, bool prime);
		void		print_colored_int(int c);
		void		rotate_swap(int j, bool prime);
		void		movement_U(bool prime, int nb_rota);
		void		movement_R(bool prime, int nb_rota);
		void		movement_L(bool prime, int nb_rota);
		void		movement_D(bool prime, int nb_rota);
		void		movement_F(bool prime, int nb_rota);
		void		movement_B(bool prime, int nb_rota);
		void		reduce_moves();
		void		read_movelist(t_move *movelist);
		t_move		*get_moves();
		bool		is_move_modified(char letter, char newletter);
		int			cube_array[6][3][3];
		std::string	moves;
		int			nb_moves;
};