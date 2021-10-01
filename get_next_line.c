#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
 * Take as an example a file to do the whole thing then just add an exception to read the strdin (fd 2 or 3)
 * My function need to print out only the first string before I hit a return 
 * Since my function needs to get call in a loop it should only return one line at a time always
 * I need to store the remains of my buffer into someting and clear that before I try to read again the next iteration
 * */

#define BUFFER_SIZE 4096

char *get_next_line(int fd)
{
	char		output;
	static char	*tmp;
	int			ret;
	int			i;

	output = malloc(sizeof(char) * BUFFER_SIZE + 1);
	i = 0;
	ret = read(fd,tmp,BUFFER_SIZE);
	while(tmp[i] != '\n')
		output[i] = tmp[i];
//	tmp = *(tmp) + i;
	return (output);
}

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
		ft_putchar(str[i]);
}
#include <stdio.h>
int main()
{
	int fd;
	int ret;
	static char *buf;
   
	buf = malloc(sizeof(char) *	BUFFER_SIZE + 1);

	//Here I just open my file with readonly and place the output of open in the int fd with the protection bellow
	fd = open("test", O_RDONLY);
	if (fd == -1)
		return (1);
	//here I read into my FD and I stock this into my buffer buf . I read BUFFER SIZE into the fd
	ret = read(fd, buf, BUFFER_SIZE);
		ft_putstr(get_next_line(fd));
	//here I just nul terminate my string;
//	buf[ret] = '\0'; 
//	printf("This is my buf = %s\n", buf);
	
	free(buf);
}




