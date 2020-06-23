/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyu <seyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 16:12:03 by seyu              #+#    #+#             */
/*   Updated: 2020/06/23 18:20:13 by seyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAZE_H
# define MAZE_H

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "ft_printf/ft_printf.h"

struct	s_path
{
	size_t	x;
	size_t	y;
	char	*path;
};
typedef	struct s_path	t_path;

t_path	*path_new(size_t x, size_t y, char *path);
void	path_delete(t_path **path);

char	**maze_open(const char *path);
char	*maze_solve(const char **maze);
void	maze_close(char ***maze);

#endif
