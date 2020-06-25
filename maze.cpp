/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyu <seyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 17:12:12 by seyu              #+#    #+#             */
/*   Updated: 2020/06/25 12:08:42 by seyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <list>
#include <queue>
#include <cstring>
#include "maze.hpp"

using namespace std;

Maze::Maze(char start, char end, char blank)
{
	this->map = NULL;
	this->start_chr = start;
	this->end_chr = end;
	this->blank_chr = blank;
	this->start_x = string::npos;
	this->start_y = 0;
	this->end_x = string::npos;
	this->end_y = 0;
}

Maze::Maze(string file_path)
{
	ifstream		fs(file_path);
	list<string>	map_list;
	string			line;
	size_t			pos;
	bool			set_start = false;
	bool			set_end = false;

	if (!fs.is_open())
	{
		this->map = NULL;
		return ;
	}
	getline(fs, line);
	this->start_chr = line.at(0);
	this->end_chr = line.at(1);
	this->blank_chr = line.at(2);
	while (getline(fs, line))
	{
		if (line.size() == 0)
			continue;
		else if (mapsize_x == 0)
			mapsize_x = line.size();
		else if (mapsize_x != line.size())
		{
			this->map = NULL;
			return ;
		}
		if ( (pos = line.find(start_chr)) != string::npos)
		{
			if (line.find(start_chr, pos + 1) != string::npos || set_start)
			{
				this->map = NULL;
				return ;
			}
			start_x = pos;
			start_y = map_list.size();
			set_start = true;
		}
		if ( (pos = line.find(end_chr)) != string::npos)
		{
			if (line.find(end_chr, pos + 1) != string::npos || set_end)
			{
				this->map = NULL;
				return ;
			}
			end_x = pos;
			end_y = map_list.size();
			set_end = true;
		}
		map_list.push_back(line);
	}
	if (map_list.size() > 0 && set_start && set_end)
	{
		this->map = (char **)malloc(sizeof(char *) * map_list.size());
		this->mapsize_y = map_list.size();
		for (size_t itr = 0; map_list.size() > 0; itr++, map_list.pop_front())
			(this->map)[itr] = strdup(map_list.front().c_str());
	}
	else
	{
		this->map = NULL;
		return ;
	}
	fs.close();
}

Maze::~Maze()
{
	if (map)
	{
		for (size_t itr = 0; itr < mapsize_y; itr++)
		{
			free(map[itr]);
			map[itr] = NULL;
		}
		free(map);
		map = NULL;
	}
}

bool	Maze::is_valid()
{
	if (map == NULL)
		return (false);
	if (start_chr == end_chr || start_chr == blank_chr || end_chr == blank_chr)
		return (false);
	return (true);
}

bool	Maze::is_valid(const size_t x, const size_t y)
{
	if (map[y][x] == blank_chr || map[y][x] == end_chr)
	{
		map[y][x] = start_chr;
		return (true);
	}
	else
		return (false);
}

string	Maze::solve()
{
	queue<set>	solv_queue;

	if (!is_valid())
		return ("");
	solv_queue.push({start_x, start_y, ""});
	while (!solv_queue.empty())
	{
		set	solv_set;

		solv_set = solv_queue.front();
		solv_queue.pop();
		if (solv_set.x == end_x && solv_set.y == end_y)
			return (solv_set.path);

		if (solv_set.x < mapsize_x - 1 && is_valid(solv_set.x + 1, solv_set.y))
			solv_queue.push({solv_set.x + 1, solv_set.y, solv_set.path + 'R'});
		if (solv_set.x > 0 && is_valid(solv_set.x - 1, solv_set.y))
			solv_queue.push({solv_set.x - 1, solv_set.y, solv_set.path + 'L'});
		if (solv_set.y < mapsize_y - 1 && is_valid(solv_set.x, solv_set.y + 1))
			solv_queue.push({solv_set.x, solv_set.y + 1, solv_set.path + 'D'});
		if (solv_set.y > 0 && is_valid(solv_set.x, solv_set.y - 1))
			solv_queue.push({solv_set.x, solv_set.y - 1, solv_set.path + 'U'});
	}
	return ("");
}

void	Maze::print()
{
	cout << "Start Point = (" << start_x << ", " << start_y << ")" << endl;
	cout << "End Point = (" << end_x << ", " << end_y << ")" << endl;
	cout << "Map Size = (" << mapsize_x << ", " << mapsize_y << ")" << endl;
	cout << "Start Character = \'" << start_chr << "\'" << endl;
	cout << "End Character = \'" << end_chr << "\'" << endl;
	cout << "Blank Character = \'" << blank_chr << "\'" << endl;
	if (!is_valid())
		return ;
	for (size_t y_itr = 0; y_itr < mapsize_y; y_itr++)
	{
		for (size_t x_itr = 0; x_itr < mapsize_x; x_itr++)
			cout << map[y_itr][x_itr];
		cout << endl;
	}
}
