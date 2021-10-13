/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 08:28:10 by pirichar          #+#    #+#             */
/*   Updated: 2021/10/13 07:56:35 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	to_find(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != c && str[i])
	{
		i++;
	}
	if (str[i] == c)
		return (i + 1);
	else
		return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*free_stuff(char *saved, int i)
{
	char	*tmp;
	
	tmp = ft_substr(saved, i + 1, ft_strlen(saved) - i);
	free (saved);
	saved = tmp;
	return (saved);
}


char	*next_line(int fd,  char *saved)
{
	int		ret;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	ret = read(fd, buf, BUFFER_SIZE);
	if (ret <= 0)
	{
		free (saved);
		return (NULL);
	}
	buf[ret] = '\0';
	saved = ft_strjoin_free(saved, buf);
	free (buf);
	return (saved);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*saved = NULL;
	int			i;
	if (!saved)
		saved = ft_strdup("");
	i = 0;
	while (!to_find(saved, '\n'))
	{
		saved = next_line(fd, saved);
		if (saved == NULL)
		{
			free (saved);
			return (NULL);
		}
	}
	while (saved[i] && saved[i] != '\n')
		i++;
	line = ft_substr(saved, 0, i + 1);
	saved = free_stuff(saved, i);
	return (line);
}
