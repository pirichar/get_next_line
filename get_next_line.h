/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 09:13:52 by pirichar          #+#    #+#             */
/*   Updated: 2021/10/12 10:03:29 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

char	*ft_strjoin_free(char *s1, char const *s2);
size_t	strlen_c(char *s, char c);
char	*ft_strncpy(char *dest, char *src, size_t n);
char	*get_next_line(int fd);

 

#endif
