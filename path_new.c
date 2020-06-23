/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyu <seyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:17:17 by seyu              #+#    #+#             */
/*   Updated: 2020/06/23 18:19:06 by seyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maze.h"

t_path	*path_new(size_t x, size_t y, char *path)
{
	t_path	*new_path;

	path = malloc(sizeof(t_path));
	path->x = x;
	path->y = y;
	path->path = path;
}
