/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyu <seyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 06:39:49 by seyu              #+#    #+#             */
/*   Updated: 2020/06/23 16:50:02 by seyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include "../libft/libft.h"

/*
**	gnl_check_param()
**	@param	fd
**	@param	**line
**	@return	0: No error and success to initialize
**			1: Error detected
*/

static int	gnl_check_param(int fd, char **line)
{
	if (read(fd, NULL, 0) < 0)
		return (1);
	if (BUFFER_SIZE < 1)
		return (1);
	*line = NULL;
	return (0);
}

/*
**	gnl_strjoin()
**	re-allocate to *line and *buffer
**	@param	**line = next line pointer address
**	@param	**buffer = buffer pointer address
**	@param	next_line_size = length of line in the buffer
*/

static void	gnl_strjoin(char **line, char **buffer, size_t next_line_size)
{
	char	*join_line;
	char	*dup_buffer;

	if (*line == NULL)
	{
		*line = malloc(sizeof(char));
		(*line)[0] = '\0';
	}
	if ((*buffer)[next_line_size] == '\0')
		dup_buffer = ft_strdup("");
	else if ((*buffer)[next_line_size] == '\n')
		dup_buffer = ft_strdup(*buffer + next_line_size + 1);
	else
		return ;
	(*buffer)[next_line_size] = '\0';
	join_line = ft_strjoin(*line, *buffer);
	free(*line);
	free(*buffer);
	*line = join_line;
	*buffer = dup_buffer;
}

/*
**	gnl_read_buffer()
**	@param	char	*buffer
**	@param	char	**line
**	@return	0 : Success
**			1 : No new-line character in buffer of file parameter
*/

static int	gnl_read_buffer(char **buffer, char **line)
{
	ssize_t	itr;
	int		rtn;

	itr = 0;
	while ((*buffer)[itr] != '\0' && (*buffer)[itr] != '\n')
		itr += 1;
	if ((*buffer)[itr] == '\n')
		rtn = 0;
	else
		rtn = 1;
	gnl_strjoin(line, buffer, itr);
	return (rtn);
}

/*
**	gnl_read_file()
**	@param	int		fd
**	@param	char	*buffer
**	@return	0 : Success
**			1 : Nothing to read (EOF)
**			-1 : Invalid file descriptor of the file parameter
*/

static int	gnl_read_file(int fd, char **buffer)
{
	ssize_t	read_rtn;

	if (*buffer)
		free(*buffer);
	*buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	read_rtn = read(fd, *buffer, BUFFER_SIZE);
	if (read_rtn < 0)
		return (-1);
	else if (read_rtn == 0)
		return (1);
	return (0);
}

/*
**	get_next_line()
**	@param	fd
**	@param	**line
**	@return	1 : A line has been read
**			0 : EOF has been reached
**			-1 : An error happened
*/

int			get_next_line(int fd, char **line)
{
	static char	*buffer[MAX_FD];

	if (gnl_check_param(fd, line))
		return (-1);
	if (!buffer[fd])
		gnl_read_file(fd, &buffer[fd]);
	while (gnl_read_buffer(buffer + fd, line))
	{
		if (gnl_read_file(fd, &buffer[fd]))
		{
			if (ft_strlen(*line) == 0)
			{
				free(buffer[fd]);
				buffer[fd] = NULL;
				return (0);
			}
			break ;
		}
	}
	return (1);
}
