#include "get_next_line.h"

/*Calling your function get_next_line in a loop will then allow you to read the text
 *available on the file descriptor one line at a time until the end of it.
 *Your function should return the line that has just been read. If there is nothing
 *else to read or if an error has occurred it should return NULL
 *Important: The returned line should include the ’\n’, except if you have reached
the end of file and there is no ’\n’.*/

char    *get_next_line(int fd)
{
    static char		*saved;
    char			buff[BUFFER_SIZE + 1];
    ssize_t			ret;      
    char			*tmp; 
    char			*rtn;
	char 			*new_line;

    if (fd < 0)
        return (NULL);
	ret = BUFFER_SIZE;
    while (ret == BUFFER_SIZE)
    {
	ret = read(fd, buff, BUFFER_SIZE);
	if (ret == -1)
	{
		return (NULL);
	}
        buff[ret] = '\0';
        if (saved == NULL)
            saved = ft_strdup(buff);
        else
        {
            tmp = ft_strjoin(saved, buff);
            free (saved);
            saved = tmp;
        }
	new_line = ft_strchr(saved, '\n');
        if (new_line)
            break ;
    }
	if (new_line)
	{
	    rtn = ft_substr(saved, 0, (new_line - saved + 1));
		saved = free_stuff(saved, new_line);
	}
	else 
	{
		rtn = saved;
		saved = NULL;
		if (!*rtn)
		{
			free(rtn);
			rtn = NULL;
		}
	}
	return (rtn);
}

char	*free_stuff(char *saved, char *new_line)
{
	char	*tmp;

	tmp = ft_substr(new_line, 1, ft_strlen(new_line));
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
