/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyu <seyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 16:30:35 by seyu              #+#    #+#             */
/*   Updated: 2020/06/23 17:28:20 by seyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "maze.h"

char	*g_error_msg;

static int	is_valid_maze_line(char *maze_line)
{
	size_t	itr;

	itr = 0;
	while (maze_line[itr])
	{
		if (maze_line[itr] != '^' && maze_line[itr] != '$'
				&& maze_line[itr] != '#' && maze_line[itr] != ' ')
			return (0);
		itr++;
	}
	return (1);
}

static int	is_valid_maze(char **maze)
{
	size_t	x_size;

	if (!maze || !*maze)
	{
		g_error_msg = "No maze entered.\n";
		return (0);
	}
	x_size = ft_strlen(*maze);
	while (*maze)
	{
		if (ft_strlen(*maze) != x_size)
			;//ft_printf("Maze, not square, is given as input.\n");
		else if (!is_valid_maze_line(*maze))
			;//ft_printf("Maze contains invalid characters.\n");
		else
		{
			maze++;
			continue ;
		}
		return (0);
	}
	return (1);
}

static int	extend_maze_line(char ***prev_maze, size_t *capacity)
{
	size_t	itr;
	char	**new_maze;

	if (!(new_maze = ft_calloc(sizeof(char *), *capacity * 2 + 1)))
	{
		maze_close(&new_maze);
		return (0);
	}
	*capacity = *capacity * 2;
	itr = -1;
	while ((*prev_maze)[++itr])
		new_maze[itr] = ft_strdup((*prev_maze)[itr]);
	maze_close(prev_maze);
	*prev_maze = new_maze;
	return (1);
}

char		**maze_open(const char *path)
{
	int		fd;
	size_t	itr;
	size_t	capacity;
	char	*line;
	char	**maze;

	if (!(maze = ft_calloc(sizeof(char *), 2)))
		return (NULL);
	capacity = 1;
	fd = open(path, O_RDONLY);
	itr = 0;
	while (get_next_line(fd, &line))
	{
		if (capacity == itr)
			extend_maze_line(&maze, &capacity);
		maze[itr++] = line;
		line = NULL;
	}
	if (!is_valid_maze(maze))
	{
		maze_close(&maze);
		return (NULL);
	}
	close(fd);
	return (maze);
}
