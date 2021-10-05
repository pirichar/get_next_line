#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>

//int read(int fd, char *buf, int count)
//fd = fd from where it reads
//buf = buffer of destination (where it's gonna be located)
//count = nombre d'octets à lire
//read renvois le nombre d'octets lus ou -1 en cas d'erreurs
char	*ft_strjoin(char *s1, const char *s2);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_substr(const char *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4096
#endif

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

char	*next_line(int fd,int ret, char *buf, char *saved)
{													// I HAVE TO SOLVE THIS AS WELL ( CREATE A TEMP AND FREE SAVED ?)
	ret = read(fd,buf,BUFFER_SIZE);
	buf[ret] = '\0';
	saved = ft_strjoin(saved,buf);
	if (ret < BUFFER_SIZE)
	{
		ret = read(fd,buf,BUFFER_SIZE);
		buf[ret] = '\0';
		saved = ft_strjoin(saved,buf);
	}
		return (saved);
}

char *get_next_line(int fd)
{
	char		*line;
	static char *saved;
	int			ret;
	char		buf[BUFFER_SIZE + 1];
	int 		i;
														// I HAVE TO ADD A PROTECTION FOR NEGATIVE FDs
	if(!saved)
	{
		saved = malloc(sizeof(char) * 4086);			// I have TO SOLVE THIS
		if (!saved)
			return (NULL);
	}
	ret = 1;
	i = 0;
	while (nl_find(saved) == 0)
		saved = next_line(fd,ret,buf,saved);
	while(saved[i] && saved[i] != '\n')
		i++;
	line = ft_substr(saved,0, i + 1);					//I HAVE TO SOLVE THIS 
	saved = saved + i + 1;								// I HAVE TO SOLVE THIS
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

char	*ft_strjoin(char *s1, const char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);	
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
//	if (s1)
//		free (s1);
	return (str);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		num;

	str = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (str == NULL)
	{
		return (0);
	}
	num = ft_strlcpy(str, s1, sizeof(char) * (ft_strlen(s1) + 1));
	*(str + ft_strlen(s1)) = '\0';
	return (str);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (0);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (src[count])
	{
		count++;
	}
	if (size > 0)
	{
		while (src[i] && size != 0 && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (count);
}

