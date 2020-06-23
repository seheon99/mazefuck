/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mazefuck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyu <seyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 03:07:58 by seyu              #+#    #+#             */
/*   Updated: 2020/06/23 17:54:53 by seyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "maze.h"
#include "ft_printf/ft_printf.h"
#include "get_next_line/get_next_line.h"

#include <stdio.h>

int		Mazefuck(const char *path)
{
	char	**maze;

	maze = maze_open(path);
	for (size_t itr = 0; maze[itr]; itr++)
		printf("%s\n", maze[itr]);
	maze_close(&maze);
	return (1);
}

int		main(int argc, char **argv)
{
	size_t	itr;

	itr = 1;
	while (itr < argc)
	{
		Mazefuck(argv[itr]);
		itr++;
	}
}
