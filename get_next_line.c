#include "get_next_line.h"

/*Calling your function get_next_line in a loop will then allow you to read the text
 *available on the file descriptor one line at a time until the end of it.
 *Your function should return the line that has just been read. If there is nothing
 *else to read or if an error has occurred it should return NULL
 *Important: The returned line should include the ’\n’, except if you have reached
the end of file and there is no ’\n’.*/
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int     find_c(char *str, char c);
char	*ft_strchr(const char *s, int c);
char	*free_stuff(char *saved, int i);

char    *get_next_line(int fd)
{
    static char     *saved;
    char            buff[BUFFER_SIZE + 1];
    int             ret;      
    char            *tmp; 
    char            *rtn;
    int             i;

    if ( fd < 0)
        return (NULL);
    while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
    {
        buff[ret] = '\0';
        if (saved == NULL)
            saved = ft_strdup(buff);
        else
        {
            tmp = ft_strjoin(saved, buff);
            free (saved);
            saved = tmp;
        }
        if (ft_strchr(saved, '\n'))
            break;
    }
    rtn = malloc( sizeof(char) * ft_strlen(saved));
    i = 0;
    while(saved[i] && saved[i] != '\n')
        i++;
    rtn = ft_substr(saved, 0, i + 1);
	saved = free_stuff(saved, i);
	return (rtn);
}

char	*free_stuff(char *saved, int i)
{
	char	*tmp;

	tmp = ft_substr(saved, i + 1, ft_strlen(saved) - i);
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



int     find_c(char *str, char c)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (i + 1);
        i++;
    }
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

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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
