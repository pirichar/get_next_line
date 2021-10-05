#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

//int read(int fd, char *buf, int count)
//fd = fd from where it reads
//buf = buffer of destination (where it's gonna be located)
//count = nombre d'octets à lire
//read renvois le nombre d'octets lus ou -1 en cas d'erreurs
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

// a function to find something and return the index or where it leaves
int	strFind(char *str, char c)
{
	int	i;
	
	i = 0;
	while (str[i] && str[i] != c)
	{
		i++;
	}
	if (str[i] == c)
		return (i);
	else
		return (-2);
}


char *get_next_line(int fd)
{
	static char	*saved;
	char		*rtn;
	char		buf[BUFFER_SIZE + 1];
	static int	ret;
	int			i;

	saved = malloc(sizeof(char) * 4086);
	if (!saved)
		return (NULL);
	rtn = malloc(sizeof(char) * 4000);
	if (!rtn)
		return (NULL);
	ret = read(fd,buf,BUFFER_SIZE);
	saved = ft_strjoin(saved,buf);
	//CASE 2 - I COULDNT READ BUT I STILL HAVE STUFF IN SAVED
	if (ret < 1 && *saved != 0)
	{	
		i = 0;
		while (*saved && *saved != '\n')
			{
				rtn[i] = *saved;
				saved++;
				i++;
			}
		rtn[i] = '\n';
		*saved = *(saved ) + 1;
	}
	//CASE 1 = I READ SOMETHING AND MY SAVED ISNT NULL
	if (ret != 0 && *saved != '\0')
	{
		//IF I FIND A NEWLINE INTO MY SAVE
		if (strFind(saved, '\n') != -2)
		{
			printf("saved is = %s\n", saved);
			i = 0;
			while (*saved && *saved != '\n')
			{
				rtn[i] = *saved;
				saved++;
				i++;
			}
			rtn[i] = '\n';
			*saved = *(saved) + 1;
		}
		//IF I DON'T FIND A NEWLINE INTO MY SAVE
		else
		{
			while(strFind(saved,'\n') == -2)
			{	
				read(fd,buf,BUFFER_SIZE);
				saved = ft_strjoin(saved,buf);
				printf("saved is = %s\n", saved);
			}

			i = 0;
			while (*saved && *saved != '\n')
			{
				rtn[i] = *saved;
				saved++;
				i++;
			}
			rtn[i] = '\n';
			*saved = *(saved) + 1;
		}
	}		
	return (rtn);
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
	//Here I just open my file with readonly and place the output of open in the int fd with the protection bellow
	fd = open("test", O_RDONLY);
	if (fd == -1)
		return (1);
	fd2 = open("test2", O_RDONLY);
	if (fd == -1)
		return (1);

	test = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if(test == NULL)
		return (1);	
	printf("Printing first fd %i times = \n", x);
	while(i < x)
	{
	test = get_next_line(fd);
	printf("%s", test);
	i++;
	}
	free (test);
}











char	*ft_strjoin(const char *s1, const char *s2)
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

