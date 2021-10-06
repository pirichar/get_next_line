/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 09:13:52 by pirichar          #+#    #+#             */
/*   Updated: 2021/10/06 09:37:40 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

char	*ft_strjoin(char *s1, const char *s2);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_substr(const char *s, unsigned int start, size_t len);

int		nl_find(char *str);
char	*next_line(int fd, int ret, char *buf, char *saved);
char	*get_next_line(int fd);

#endif
