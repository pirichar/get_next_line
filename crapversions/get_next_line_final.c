#include "get_next_line.h"

// a function to find something and return the index or where it leaves
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

char *get_next_line(int fd)
{
	char		*line;
	static char *saved;
	int			ret;
	char		buf[BUFFER_SIZE + 1];
	int 		i;

	if(!saved)
	{
		saved = malloc(sizeof(char) * 4086);
		if (!saved)
			return (NULL);
	}
	ret = 1;
	i = 0;
	while (nl_find(saved) == 0)
	{
		ret = read(fd,buf,BUFFER_SIZE);
		buf[ret] = '\0';
		saved = ft_strjoin(saved,buf);
		if(ret < BUFFER_SIZE)
		{
			ret = read(fd,buf,BUFFER_SIZE);
			buf[ret] = '\0';
			saved = ft_strjoin(saved,buf); // je pourrais modifier ma fonction str
		}
	}
	while(saved[i] && saved[i] != '\n')
		i++;
	line = ft_substr(saved,0, i + 1);
	saved = saved + i + 1;
	return (line);
}

int main()
{
	int fd;
	int fd2;
	char *test;
//	char *test2;
	int i;
	int x;

	i = 0;
	x = 7;
	fd = open("test", O_RDONLY);
	if (fd == -1)
		return (1);
	fd2 = open("test2", O_RDONLY);
	if (fd == -1)
		return (1);

	test = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if(test == NULL)
		return (1);	
//	printf("FROM MAIN : Printing first fd %i times = \n", x);
	while(i < x)
	{
	test = get_next_line(fd);
	printf("FROM MAIN : %s", test);
	i++;
	free (test);
	}
}
