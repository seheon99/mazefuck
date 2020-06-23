/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze_solve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyu <seyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 17:56:56 by seyu              #+#    #+#             */
/*   Updated: 2020/06/23 18:15:33 by seyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdlib.h>

static int	find_start_point(const char **maze, size_t *x, size_t *y)
{
	size_t	x_itr;
	size_t	y_itr;

	y_itr = 0;
	while (maze[y_itr])
	{
		x_itr = 0;
		while (maze[y_itr][x_itr] && maze[y_itr][x_itr] != '^')
			;
		if (maze[y_itr][x_itr] == '^')
			break ;
	}
}

char	*maze_solve(const char **maze)
{
	t_list	**calc;

	return (path);
}
