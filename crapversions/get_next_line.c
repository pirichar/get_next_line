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

//Defenition of the function :
/* 1- Calling get_next_line in a loop will allow you to read the text 
 * available in the fd one line at the time untill the end of it 
 * 2-Your Function should return the line that has just been read.
 * if there is nothing else to read or if an error occured it should return NULL
 * 3- make sure that the function behaves well when it reads
 * from a file and when it reads from the standard input
 * 4- Libft is not allowed here,you must add a get_next_line_utils.c
 * file if you need more functions to make your function work.
 * 5-Your program must compile with the flag -D BUFFER_SIZE = XX
 * which will be used as the buffer size for the read calls.
 * this value will be modified by your evaluators and the moulinette
 * 6-The program will be compile this way :
 * gcc -Wall -Werror -Wextra -D BUFFER_SIZE=42 <files>.c
 * 7-Your read must use the BUFFER_SIZE defined during 
 * the compilation to read from a fil or strdin.
 * 8- In the header fil get_next_line.h you must have at least
 * the prototype of the function get_next_line.
 * 9- the returned line should include the '\n' exceot if you
 * have reached the end of file and there is no '\n'
 */

/*to do list :
 * Take as an example a file to do the whole thing then just add an 
 * exception to read the strdin (fd 2 or 3)
 * My function need to print out only the first string before I hit a return 
 * Since my function needs to get call in a loop it should only return one line at a time always
 * I need to store the remains of my buffer into someting and clear 
 * that before I try to read again the next iteration
 * */

//#define BUFFER_SIZE 4096
//
int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while(s[i])
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

char *get_next_line(int fd)
{
	static char	*output;
	char		*tmp = NULL;
	char		*rtn;
	int		ret;
	int		i;
	int		j;

	if(!output)
		output = malloc(sizeof(char) * 4000 + 1);
			if(!output)
				return (NULL);
	if(!tmp)
		tmp = malloc(sizeof(char) * 4000 + 1);
			if(!tmp)
				return (NULL);
	i = 0;
	//here I read into fd and I get everything 
	while ((ret = read(fd,tmp,BUFFER_SIZE)) != 0)
	{
		while(*tmp)
		{
			output[i] = *tmp;
			i++;
			tmp++;
		}
		tmp[ret] = '\0';
	}
//	here I copy from output to rtn untill I hit my new line
//	then i add the new line
	i = 0;
	rtn = malloc(sizeof(char) * 4000 + 1);
	while(*output != '\n')
	{
		rtn[i] = *output;
		i++;
		output++;
	}
	rtn[i] = '\n';
	//Here I move my output pointer so it points
	//at the right place which is after the \n 
	j = 0;
	while(output[j] == '\n')
		j++;
	*output = *(output) + j;
	return (rtn);
}

#include <stdio.h>
int main()
{
	int fd;
	char *test;
	int i;

	i = 0;
	//Here I just open my file with readonly and place the output of open in the int fd with the protection bellow
	fd = open("test", O_RDONLY);
	if (fd == -1)
		return (1);
	test = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if(test == NULL)
		return (1);	
	printf("This is me using my function to print out a sentence after opening fd with read\n");
	while(i < 3)
	{
	test = get_next_line(fd);
	printf("%s", test);
	i++;
	}
	free (test);
}




