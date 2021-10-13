/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 08:27:28 by pirichar          #+#    #+#             */
/*   Updated: 2021/10/12 17:01:30 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <fcntl.h>

int main()
{
	int fd;
//	int fd2;
	char *test;
//	char *test2;
	int i;
	int x;

	i = 0;
	x = 7;
	fd = open("test", O_RDONLY);
	if (fd == -1)
		return (1);
/*	fd2 = open("test2", O_RDONLY);
	if (fd == -1)
		return (1);*/

	//	printf("FROM MAIN : Printing first fd %i times = \n", x);
	while(i < x)
	{
	test = get_next_line(fd);
	printf("FROM MAIN : %s", test);
	i++;
	free (test);
	}
}
