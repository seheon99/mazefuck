/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyu <seyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 15:43:55 by seyu              #+#    #+#             */
/*   Updated: 2020/06/23 15:44:12 by seyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maze.h"

void	maze_close(char ***maze)
{
	size_t	itr;

	itr = 0;
	if (!maze || !*maze)
		return ;
	while ((*maze)[itr])
	{
		free((*maze)[itr]);
		(*maze)[itr] = 0;
	}
	free(*maze);
	*maze = 0;
}

