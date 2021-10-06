/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 08:28:10 by pirichar          #+#    #+#             */
/*   Updated: 2021/10/06 14:42:53 by pirichar         ###   ########.fr       */
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
	tmp = ft_strjoin(saved, buf);
	free (saved);
	saved = tmp;
	if (ret < BUFFER_SIZE)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return NULL;	
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
	{	
		saved = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!saved)
			return (NULL);
	}
	ret = 1;
	i = 0;
	while (nl_find(saved) == 0)
		saved = next_line(fd, ret, buf, saved);
	if (!saved)
		return NULL;
	while (saved[i] && saved[i] != '\n')
		i++;
	line = ft_substr(saved, 0, i + 1);
	saved = free_stuff(saved, i);
	return (line);
}
