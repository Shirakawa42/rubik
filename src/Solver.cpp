#include "Solver.hpp"

Solver::Solver()
{

}

Solver::~Solver()
{

}

void	Solver::solve(Cube & cube)
{
	cube.reset_moves();
	create_blue_face(cube);
}

void	Solver::set_facing(int face)
{
	if (face == 0)
	{
		U = "F";
		D = "B";
		R = "L";
		L = "R";
		F = "U";
		B = "D";
	}
	if (face == 1)
	{
		U = "F";
		D = "B";
		R = "D";
		L = "U";
		F = "L";
		B = "R";
	}
	if (face == 2)
	{
		U = "U";
		D = "D";
		R = "R";
		L = "L";
		F = "F";
		B = "B";
	}
	if (face == 3)
	{
		U = "F";
		D = "B";
		R = "U";
		L = "D";
		F = "R";
		B = "L";
	}
	if (face == 4)
	{
		U = "U";
		D = "D";
		R = "L";
		L = "R";
		F = "B";
		B = "F";
	}
	if (face == 5)
	{
		U = "F";
		D = "B";
		R = "R";
		L = "L";
		F = "D";
		B = "U";
	}
}

static bool	is_arete_opposite(int i, int j, int k)
{
	if ((i == 1 && j == 1 && k == 0)
		|| (i == 0 && j == 0 && k == 1)
		|| (i == 3 && j == 1 && k == 2)
		|| (i == 5 && j == 2 && k == 1))
		return true;
	return false;
}

static void	get_down(int facing, int & j, int & k)
{
	if (facing == 0)
	{
		j = 0;
		k = 1;
	}
	else if (facing == 1)
	{
		j = 1;
		k = 0;
	}
	else if (facing == 3)
	{
		j = 1;
		k = 2;
	}
	else if (facing == 5)
	{
		j = 2;
		k = 1;
	}
}

static void	get_4_placement(int facing, int & j, int & k)
{
	if (facing == 0)
	{
		j = 0;
		k = 1;
	}
	else if (facing == 1)
	{
		j = 1;
		k = 2;
	}
	else if (facing == 3)
	{
		j = 1;
		k = 0;
	}
	else if (facing == 5)
	{
		j = 2;
		k = 1;
	}
}

static bool	is_arete_side(int i, int j, int k)
{
	if ((i == 0 && j == 1 && k == 0)
		|| (i == 0 && j == 1 && k == 2)
		|| (i == 3 && j == 0 && k == 1)
		|| (i == 3 && j == 2 && k == 1)
		|| (i == 5 && j == 1 && k == 0)
		|| (i == 5 && j == 1 && k == 2)
		|| (i == 1 && j == 0 && k == 1)
		|| (i == 1 && j == 2 && k == 1))
		return true;
	return false;
}

static void	get_nearest_arete(int facing, int & j, int & k)
{
	if (facing == 0)
	{
		j = 0;
		k = 1;
	}
	else if (facing == 1)
	{
		j = 1;
		k = 0;
	}
	else if (facing == 3)
	{
		j = 1;
		k = 2;
	}
	else if (facing == 5)
	{
		j = 2;
		k = 1;
	}
}

static int	get_nearest_face(int j, int k)
{
	if (j == 2 && (k == 1 || k == 2))
		return 5;
	if (j == 0 && (k == 0 || k == 1))
		return 0;
	if (k == 0 && (j == 1 || j == 2))
		return 1;
	return 3;
}

static bool	is_blue_arete(int val)
{
	if (val == 19 || val == 21 || val == 23 || val == 25)
		return true;
	return false;
}

static bool	is_arete_top(int i, int j, int k)
{
	if ((i == 3 && j == 1 && k == 0)
		|| (i == 0 && j == 2 && k == 1)
		|| (i == 1 && j == 1 && k == 2)
		|| (i == 5 && j == 0 && k == 1))
		return true;
	return false;
}

void	Solver::place_arete(Cube & cube, int i, int j, int k, int facing, int value)
{
	int	nj, nk;
	int	nb = 0;

	set_facing(facing);
	if (i == 4)
	{
		get_4_placement(facing, nj, nk);
		while (cube.get_value(4, nj, nk) != value)
			cube.move('B', false, 1);
		parser.Parse((L+"'"+R+F+F+L+R+"'").c_str(), cube);
		return ;
	}
	if (is_arete_top(i, j, k))
	{
		set_facing(i);
		parser.Parse((F).c_str(), cube);
		set_facing(facing);
		cube.find_value(value, i, j, k);
	}
	if (i == 2)
	{
		set_facing(get_nearest_face(j, k));
		parser.Parse((F).c_str(), cube);
		set_facing(facing);
		cube.find_value(value, i, j, k);
	}
	if (is_arete_side(i, j, k))
	{
		set_facing(i);
		get_nearest_arete(i, nj, nk);
		while (is_blue_arete(cube.get_value(2, nj, nk)))
		{
			cube.move('F', false, 1);
			nb++;
		}
		while (!is_arete_opposite(i, j, k))
		{
			parser.Parse((F).c_str(), cube);
			cube.find_value(value, i, j, k);
		}
		for (int h = 0; h < nb; h++)
			cube.move('F', true, 1);
		nb = 0;
		set_facing(facing);
	}
	if (is_arete_opposite(i, j, k))
	{
		get_down(facing, nj, nk);
		while (cube.get_value(facing, nj, nk) != value)
			cube.move('B', false, 1);
		parser.Parse((D+R+L+"'"+F+"'"+R+"'"+L).c_str(), cube);
		return ;
	}
}

static bool	is_blue_corner(int val)
{
	if (val == 18 || val == 20 || val == 24 || val == 26)
		return true;
	return false;
}

static void	get_nearest_corner_from_back(int j, int k, int & nj, int & nk)
{
	if (j == 0 && k == 0)
	{
		nj = 0;
		nk = 2;
	}
	else if (j == 0 && k == 2)
	{
		nj = 0;
		nk = 0;
	}
	else if (j == 2 && k == 0)
	{
		nj = 2;
		nk = 2;
	}
	else if (j == 2 && k == 2)
	{
		nj = 2;
		nk = 0;
	}
}

static bool	is_corner_top(int i, int j, int k, bool & right)
{
	if ((i == 0 && j == 2 && k == 0)
		|| (i == 1 && j == 2 && k == 2)
		|| (i == 5 && j == 0 && k == 2)
		|| (i == 3 && j == 0 && k == 0))
	{
		right = true;
		return true;
	}
	if ((i == 0 && j == 2 && k == 2)
		|| (i == 1 && j == 0 && k == 2)
		|| (i == 5 && j == 0 && k == 0)
		|| (i == 3 && j == 2 && k == 0))
	{
		right = false;
		return true;
	}
	return false;
}

static void	get_down_corner(int i, int & nj, int & nk, bool right)
{
	if (i == 0)
	{
		nj = 0;
		nk = (right) ? 0 : 2;
	}
	else if (i == 1)
	{
		nj = (right) ? 2 : 0;
		nk = 0;
	}
	else if (i == 5)
	{
		nj = 2;
		nk = (right) ? 2 : 0;
	}
	else if (i == 3)
	{
		nj = (right) ? 0 : 2;
		nk = 2;
	}
}

void	Solver::place_corner(Cube & cube, int i, int j, int k, int facing, int value)
{
	int	nj, nk, njL, nkL;
	int	nb = 0;
	bool right;

	if (is_corner_top(i, j, k, right))
	{
		set_facing(i);
		if (right)
			parser.Parse((R+"'"+D+"'"+R).c_str(), cube);
		else
			parser.Parse((L+D+L+"'").c_str(), cube);
		cube.find_value(value, i, j, k);
	}
	if (i == 4)
	{
		get_nearest_corner_from_back(j, k, nj, nk);
		while (is_blue_corner(cube.get_value(2, nj, nk)))
		{
			cube.move('F', false, 1);
			nb++;
		}
		set_facing(get_nearest_face(nj, nk));
		parser.Parse((R+"'"+D+R).c_str(), cube);
		for (int h = 0; h < nb; h++)
			cube.move('F', true, 1);
		nb = 0;
	}
	if (i == 2)
	{
		set_facing(get_nearest_face(j, k));
		parser.Parse((R+"'"+D+"'"+R).c_str(), cube);
	}
	set_facing(facing);
	get_down_corner(facing, nj, nk, true);
	get_down_corner(facing, njL, nkL, false);
	while (cube.get_value(facing, nj, nk) != value && cube.get_value(facing, njL, nkL) != value)
		cube.move('B', false, 1);
	if (cube.get_value(facing, nj, nk) == value)
		parser.Parse((D+"'"+R+"'"+D+R).c_str(), cube);
	else
		parser.Parse((D+D+F+D+"'"+F+"'").c_str(), cube);
}

void	Solver::create_blue_face(Cube & cube)
{
	int				i, j, k;

	cube.find_value(19, i, j, k);
	if (!(i == 2 && j == 0 && k == 1))
		place_arete(cube, i, j, k, 0, 19);
	cube.find_value(21, i, j, k);
	if (!(i == 2 && j == 1 && k == 0))
		place_arete(cube, i, j, k, 1, 21);
	cube.find_value(23, i, j, k);
	if (!(i == 2 && j == 1 && k == 2))
		place_arete(cube, i, j, k, 3, 23);
	cube.find_value(25, i, j, k);
	if (!(i == 2 && j == 2 && k == 1))
		place_arete(cube, i, j, k, 5, 25);

	cube.find_value(18, i, j, k);
	if (!(i == 2 && j == 0 && k == 0))
		place_corner(cube, i, j, k, 0, 18);
	cube.find_value(20, i, j, k);
	if (!(i == 2 && j == 0 && k == 2))
		place_corner(cube, i, j, k, 3, 20);
	cube.find_value(24, i, j, k);
	if (!(i == 2 && j == 2 && k == 0))
		place_corner(cube, i, j, k, 1, 24);
	cube.find_value(26, i, j, k);
	if (!(i == 2 && j == 2 && k == 2))
		place_corner(cube, i, j, k, 5, 26);
}