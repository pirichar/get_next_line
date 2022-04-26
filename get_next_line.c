/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 09:17:02 by pirichar          #+#    #+#             */
/*   Updated: 2022/04/26 09:37:54 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char *saved, char **new_line)
{
	char			*buff;
	ssize_t			ret;

	ret = BUFFER_SIZE;
	while (ret == BUFFER_SIZE)
	{
		buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
		{
			free (buff);
			return (NULL);
		}
		buff[ret] = '\0';
		saved = ft_strjoin_free(saved, buff);
		free (buff);
		*new_line = ft_strchr(saved, '\n');
		if (*new_line)
			break ;
	}
	return (saved);
}

char	*get_next_line(int fd)
{
	static char		*saved;
	char			*rtn;
	char			*new_line;

	saved = read_file(fd, saved, &new_line);
	if (saved == NULL)
		return (NULL);
	if (new_line)
	{
		rtn = ft_substr(saved, 0, (new_line - saved + 1));
		saved = free_stuff(saved, new_line);
	}
	else
	{
		rtn = saved;
		saved = NULL;
		if (!*rtn)
		{
			free(rtn);
			rtn = NULL;
		}
	}
	return (rtn);
}

char	*free_stuff(char *saved, char *new_line)
{
	char	*tmp;

	tmp = ft_substr(new_line, 1, ft_strlen(new_line));
	if (!*tmp)
	{
		free(tmp);
		tmp = NULL;
	}
	free(saved);
	saved = tmp;
	return (saved);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	c2;

	c2 = c;
	while (*s != c2 && *s)
		s++;
	if (*s == c2)
		return ((char *)s);
	return (0);
}
