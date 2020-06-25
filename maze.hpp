/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyu <seyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 17:12:23 by seyu              #+#    #+#             */
/*   Updated: 2020/06/25 12:08:41 by seyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAZE_HPP
# define MAZE_HPP

# include <string>

class	Maze
{
private:
	char	**map;
	char	start_chr;
	char	end_chr;
	char	blank_chr;
	size_t	mapsize_x;
	size_t	mapsize_y;
	size_t	start_x;
	size_t	start_y;
	size_t	end_x;
	size_t	end_y;
public:
	Maze(char start = '^', char end = '$', char blank = ' ');
	Maze(std::string file_path);
	~Maze();
	bool		is_valid();
	bool		is_valid(const size_t x, const size_t y);
	std::string	solve();
	void		print();
};

struct	set
{
	size_t		x;
	size_t		y;
	std::string	path;
};


#endif
