/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 08:28:10 by pirichar          #+#    #+#             */
/*   Updated: 2021/10/06 17:41:26 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	nl_find(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i])
	{
		i++;
	}
	if (str[i] == '\n')
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

char	*next_line(int fd, int ret, char *buf, char *saved)
{
	char	*tmp;

	ret = read(fd, buf, BUFFER_SIZE);
	buf[ret] = '\0';
	if(buf[0] == '\0')
	{
		free (saved);
		return (NULL);
	}
	tmp = ft_strjoin(saved, buf);
	free (saved);
	saved = tmp;
	if (ret < BUFFER_SIZE)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		buf[ret] = '\0';
		tmp = ft_strjoin(saved, buf);
		free (saved);
		saved = tmp;
	}
	return (saved);
}

char	*free_stuff(char *saved, int i)
{
	char	*tmp;

	tmp = ft_substr(saved, i + 1, ft_strlen(saved) - i);
	free(saved);
	saved = tmp;
	return (saved);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*saved;
	int			ret;
	char		buf[BUFFER_SIZE + 1];
	int			i;
	if (!saved)
		saved = ft_strdup("");
	ret = 1;
	i = 0;
	//I NEED TO FIND A WAY TO STOP THIS LOOP IF I DONT FIND A NEW LINE OR IF THE FILE IS EMPTY
	while (nl_find(saved) == 0)
	{
		saved = next_line(fd, ret, buf, saved);
		if (saved == NULL)
			return (NULL);
	}
	while (saved[i] && saved[i] != '\n')
		i++;
	line = ft_substr(saved, 0, i + 1);
	saved = free_stuff(saved, i);
	return (line);
}
