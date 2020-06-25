/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mazegen.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyu <seyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 06:32:24 by seyu              #+#    #+#             */
/*   Updated: 2020/06/25 11:59:01 by seyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <cstring>
#include "mazegen.hpp"

using namespace std;

int				g_x_inc[4] = {0, 1, 0, -1};
int				g_y_inc[4] = {-1, 0, 1, 0};

static void		change_direction(t_dir	&direction, const char command)
{
	if (command == '0')
	{
		if (direction == LEFT)
			direction = DOWN;
		else if (direction == DOWN)
			direction = RIGHT;
		else if (direction == RIGHT)
			direction = UP;
		else if (direction == UP)
			direction = LEFT;
	}
	else if (command == '1')
	{
		if (direction == LEFT)
			direction = UP;
		else if (direction == UP)
			direction = RIGHT;
		else if (direction == RIGHT)
			direction = DOWN;
		else if (direction == DOWN)
			direction = LEFT;
	}
}

Mazegen::Mazegen(const string set, string binary)
{
	t_dir	direction;
	size_t	x;
	size_t	y;

	start_char = set[0];
	end_char = set[1];
	wall_char = set[2];
	blank_char = set[3];
	mapsize_y = 4;
	mapsize_x = 3;
	map = (char **)calloc(sizeof(char *), mapsize_y);
	for (size_t itr = 0; itr < 4; itr++)
		map[itr] = (char *)calloc(sizeof(char), 4);
	map[0][0] = wall_char;	map[0][1] = wall_char;	map[0][2] = wall_char;
	map[1][0] = wall_char;	map[1][1] = start_char;	map[1][2] = wall_char;	direction = DOWN;
	map[2][0] = wall_char;	map[2][1] = blank_char;	map[2][2] = wall_char;	y = 2;	x = 1;
	map[3][0] = wall_char;	map[3][1] = wall_char;	map[3][2] = wall_char;
	for (size_t itr = 0; itr < binary.size(); itr++)
	{
		change_direction(direction, binary[itr]);
		//cout << "itr = " << itr << ", command = " << binary[itr] << endl;
		make_road(x, y, direction, (itr + 1 == binary.size()));
		//for (size_t itr_y = 0; itr_y < mapsize_y; itr_y++)
			//cout << map[itr_y] << '$' << endl;
	}
	//cout << "Success, start printing" << endl;
	//cout << "mapsize_x = " << mapsize_x << endl;
	//cout << "mapsize_y = " << mapsize_y << endl;
}

Mazegen::~Mazegen()
{
	for (size_t	itr = 0; itr < mapsize_y; itr++)
	{
		free(map[itr]);
		map[itr] = NULL;
	}
	free(map);
	map = NULL;
}

bool	Mazegen::is_surrounded(size_t x, size_t y)
{
	int count;

	count = 0;
	if (x == 0 || y == 0 || x >= mapsize_x - 1 || y >= mapsize_y - 1)
		return (false);
	for (int itr = 0; itr < 4; itr++)
	{
		if (map[y + g_y_inc[itr]][x + g_x_inc[itr]] != wall_char)
			count++;
	}
	if (count == 1)
		return (true);
	return (false);
}

void	Mazegen::make_road(size_t &x, size_t &y, const t_dir direction, bool end)
{
	if (direction == LEFT && x == 1)
	{
		extend_left();
		x += 1;
	}
	else if (direction == RIGHT && x == mapsize_x - 2)
		extend_right();
	else if (direction == UP && y == 1)
	{
		extend_top();
		y += 1;
	}
	else if (direction == DOWN && y == mapsize_y - 2)
		extend_bottom();
	else
	{
		for (int itr = 0; itr < 4; itr++)
		{
			if (itr == direction - 2 || itr == direction + 2)
				continue ;
			if (map[y + g_y_inc[direction] + g_y_inc[itr]][x + g_x_inc[direction] + g_x_inc[itr]] != wall_char)
			{
				if (g_y_inc[itr] == 1)
					new_xline(y + g_y_inc[direction]);
				else if (g_y_inc[itr] == -1)
				{
					new_xline(y + g_y_inc[direction] - 1);
					y += 1;
				}
				else if (g_x_inc[itr] == 1)
					new_yline(x + g_x_inc[direction]);
				else if (g_x_inc[itr] == -1)
				{
					new_yline(x + g_x_inc[direction] - 1);
					x += 1;
				}
			}
		}
	}
	if (end)
		map[y + g_y_inc[direction]][x + g_x_inc[direction]] = end_char;
	else
		map[y + g_y_inc[direction]][x + g_x_inc[direction]] = blank_char;
	y += g_y_inc[direction];
	x += g_x_inc[direction];
}

void	Mazegen::extend_left()
{
	new_yline(0);
}

void	Mazegen::extend_right()
{
	new_yline(mapsize_x - 2);
}

void	Mazegen::extend_top()
{
	new_xline(0);
}

void	Mazegen::extend_bottom()
{
	new_xline(mapsize_y - 2);
}

void	Mazegen::extend_in()
{
	char	**newmap;
	char	*wall_string;

	mapsize_x = (mapsize_x - 2) * 2 + 2;
	mapsize_y = (mapsize_y - 2) * 2 + 2;
	newmap = (char **)calloc(sizeof(char *), mapsize_y);
	for (size_t itr = 0; itr < mapsize_y; itr++)
		newmap[itr] = (char *)calloc(sizeof(char), mapsize_x + 1);
	wall_string = (char *)calloc(sizeof(char), mapsize_x + 1);
	for (size_t itr = 0; itr < mapsize_x; itr++)
		wall_string[itr] = wall_char;
	newmap[0] = strdup(wall_string);
	newmap[mapsize_y - 1] = strdup(wall_string);
	for (size_t itr_y = 1; itr_y < mapsize_y - 1; itr_y++)
	{
		newmap[itr_y] = strdup(wall_string);
		for (size_t itr_x = 1; itr_x < mapsize_x - 1; itr_x++)
		{
			if (itr_y % 2 == 1)
			{
				if (itr_x % 2 == 1)
					newmap[itr_y][itr_x] = map[(itr_y - 1) / 2 + 1][(itr_x - 1) / 2 + 1];
				else
				{
					if (map[(itr_y - 1) / 2 + 1][(itr_x - 1) / 2 + 1] == blank_char
							&& map[(itr_y - 1) / 2 + 1][itr_y / 2] == blank_char)
						newmap[itr_y][itr_x] = blank_char;
					else
						newmap[itr_y][itr_x] = wall_char;
				}
			}
			else
			{
				if (itr_x % 2 == 1)
				{
					if (map[(itr_y - 1) / 2 + 1][(itr_x - 1) / 2 + 1] == blank_char
							&& map[itr_y / 2][(itr_x - 1) / 2 + 1] == blank_char)
						newmap[itr_y][itr_x] = blank_char;
					else
						newmap[itr_y][itr_x] = wall_char;
				}
				else
					newmap[itr_y][itr_x] = wall_char;
			}
		}
	}
	free(wall_string);
	wall_string = NULL;
	for (size_t itr = 0; itr < (mapsize_y - 2) / 2 + 2; itr++)
	{
		free(map[itr]);
		map[itr] = NULL;
	}
	free(map);
	map = newmap;
}

void	Mazegen::new_xline(size_t y)
{
	char	**newmap;

	if (y >= mapsize_y - 1)
		return ;
	mapsize_y += 1;
	newmap = (char **)calloc(sizeof(char *), mapsize_y);
	for (size_t itr_y = 0; itr_y <= y; itr_y++)
		newmap[itr_y] = strdup(map[itr_y]);
	newmap[y + 1] = (char *)calloc(sizeof(char), mapsize_x + 1);
	for (size_t itr_x = 0; itr_x <= mapsize_x; itr_x++)
	{
		if (map[y][itr_x] != wall_char && map[y + 1][itr_x] != wall_char)
			newmap[y + 1][itr_x] = blank_char;
		else
			newmap[y + 1][itr_x] = wall_char;
	}
	for (size_t itr_y = y + 2; itr_y < mapsize_y; itr_y++)
		newmap[itr_y] = strdup(map[itr_y - 1]);
	for (size_t itr = 0; itr < mapsize_y - 1; itr++)
	{
		free(map[itr]);
		map[itr] = NULL;
	}
	free(map);
	map = newmap;
}

void	Mazegen::new_yline(size_t x)
{
	char	**newmap;

	mapsize_x += 1;
	newmap = (char **)calloc(sizeof(char *), mapsize_y);
	for (size_t itr_y = 0; itr_y < mapsize_y; itr_y++)
	{
		newmap[itr_y] = (char *)calloc(sizeof(char), mapsize_x + 1);
		for (size_t itr_x = 0; itr_x <= x; itr_x++)
			newmap[itr_y][itr_x] = map[itr_y][itr_x];
		if (map[itr_y][x] != wall_char && map[itr_y][x + 1] != wall_char)
			newmap[itr_y][x + 1] = blank_char;
		else
			newmap[itr_y][x + 1] = wall_char;
		for (size_t itr_x = x + 2; itr_x < mapsize_x; itr_x++)
			newmap[itr_y][itr_x] = map[itr_y][itr_x - 1];
	}
	for (size_t itr = 0; itr < mapsize_y; itr++)
	{
		free(map[itr]);
		map[itr] = NULL;
	}
	free(map);
	map = newmap;
}
