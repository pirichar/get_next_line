/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 09:18:29 by pirichar          #+#    #+#             */
/*   Updated: 2021/10/12 09:57:34 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static long get_line_len(char **remain, int fd)
{
	long	read_status;
	char	*read_buf;

	while (!(*remain) || !strlen_c(*remain, '\n'))
	{
		read_buf = malloc(BUFFER_SIZE + 1);
		read_status = read(fd, read_buf, BUFFER_SIZE);
		if (read_status <= 0)
		{
			free (read_buf);
			return (read_status);
		}
		read_buf[read_status] = 0;
		*remain = ft_strjoin_free(*remain, read_buf);
		free (read_buf);
	}
	return (strlen_c(*remain, '\n'));
}

char	*get_next_line(int fd)
{
	char 		*current_line;
	long		line_len;
	static char *remain;

	line_len = get_line_len(&remain, fd);
	if (line_len <= 0)
		line_len = strlen_c(remain, 0);
	if(!line_len)
	{
		free (remain);
		remain = (NULL);
		return (NULL);
	}
	current_line = malloc(line_len + 1);
	ft_strncpy(current_line, remain, line_len);
	if (!strlen_c(remain, '\n'))
	{
		free (remain);
		remain = (NULL);
	}
	else
		ft_strncpy(remain, &remain[line_len], strlen_c(remain, 0) - line_len + 1);
	return (current_line);
}
