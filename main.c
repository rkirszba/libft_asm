#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libc.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/errno.h>

#define	NB_STRINGS		11
#define MAX_STRING_LEN	100

const char	tab_str[NB_STRINGS][MAX_STRING_LEN] = {
	"",
	"bonjour",
	"bonjour\0",
	"bonjouR",
	"Bonjour",
	"bonjours",
	"adaoAIUYodjapoj\0asdajsdd",
	"345345oihhsf      ihfoi",
	"csdcs",
	"\0",
	"18"
};


extern size_t	ft_strlen(const char *s);
extern char		*ft_strcpy(char *dst, const char *src);
extern int		ft_strcmp(const char *s1, const char *s2);
extern ssize_t	ft_write(int fildes, const void *buf, size_t nbyte);


void	test_ft_strlen(void)
{
	size_t	i;
	size_t	off_len;
	size_t	my_len;

	i = 0;
	printf("------- Tests on ft_strlen --------\n\n");
	while (i < NB_STRINGS)
	{
		off_len = strlen(tab_str[i]);
		my_len = ft_strlen(tab_str[i]);
		printf("TEST %2zu: ", i);
		if (my_len != off_len)
		{
			printf("\033[31m");
			printf("FAILURE\n");
			printf("\033[39m");
			printf("Lens are different for string \"%s\"\n", tab_str[i]);
			printf("Official len = %zu\n", off_len);
			printf("My len       = %zu\n", my_len);
		}
		else
		{
			printf("\033[32m");
			printf("SUCCESS\n");
			printf("\033[39m");
		}
		i++;
	}
}

void	test_ft_strcpy(void)
{
	size_t	i;
	char	*off_str;
	char	*my_str;
	
	i = 0;
	off_str = (char*)malloc(sizeof(*off_str) * MAX_STRING_LEN);
	my_str = (char*)malloc(sizeof(*my_str) * MAX_STRING_LEN);
	i = 0;
	printf("------- Tests on ft_strcpy --------\n\n");
	while (i < NB_STRINGS)
	{
		off_str = strcpy(off_str, tab_str[i]);
		my_str = ft_strcpy(my_str, tab_str[i]);
		printf("TEST %2zu: ", i);
		if (strcmp(off_str, my_str) != 0)
		{
			printf("\033[31m");
			printf("FAILURE\n");
			printf("\033[39m");
			printf("Strings are different:\n");
			printf("Official str = \"%s\"\n", off_str);
			printf("My str       = \"%s\"\n", my_str);
		}
		else
		{
			printf("\033[32m");
			printf("SUCCESS\n");
			printf("\033[39m");
		}
		i++;
	}
}

void	test_ft_strcmp(void)
{
	size_t	i;
	size_t	j;
	int		off_cmp;
	int		my_cmp;

	i = 0;
	printf("------- Tests on ft_strcmp --------\n\n");
	while (i < NB_STRINGS)
	{
		j = 0;
		while (j < NB_STRINGS)
		{
			off_cmp = strcmp(tab_str[i], tab_str[j]);
			my_cmp = ft_strcmp(tab_str[i], tab_str[j]);
			printf("TEST %3zu: ", i * NB_STRINGS + j);
			if (off_cmp != my_cmp)
			{
				printf("\033[31m");
				printf("FAILURE\n");
				printf("\033[39m");
				printf("Cmp are different for strings \"%s\" and \"%s\":\n", tab_str[i], tab_str[j]);
				printf("Official cmp = %d\n", off_cmp);
				printf("My cmp       = %d\n", my_cmp);
			}
			else
			{
				printf("\033[32m");
				printf("SUCCESS\n");
				printf("\033[39m");
			}
			j++;
		}
		i++;
	}
}

void	test_ft_write()
{
	size_t		i;
	const char	*off_file = "off_file.txt";
	const char	*my_file = "my_file.txt";
	int			off_fd;
	int			my_fd;
	char		*off_buff;
	char		*my_buff;
	ssize_t		off_ret;
	ssize_t		my_ret;
	int			errno_1;
	int			errno_2;
	int			success;


	off_buff = (char*)malloc(sizeof(*off_buff) * MAX_STRING_LEN);
	my_buff = (char*)malloc(sizeof(*my_buff) * MAX_STRING_LEN);
	i = 0;
	printf("------- Tests on ft_write --------\n\n");
	while (i < NB_STRINGS)
	{
		off_fd = open(off_file, O_RDWR | O_CREAT, S_IRWXU);
		my_fd = open(my_file, O_RDWR | O_CREAT, S_IRWXU);
		off_ret = write(off_fd, tab_str[i], strlen(tab_str[i]));
		my_ret = ft_write(my_fd, tab_str[i], strlen(tab_str[i]));
		close(off_fd);
		close(my_fd);
		off_fd = open(off_file, O_RDONLY);
		my_fd = open(my_file, O_RDONLY);
		bzero(off_buff, MAX_STRING_LEN);
		bzero(my_buff, MAX_STRING_LEN);
		read(off_fd, off_buff, strlen(tab_str[i]));
		read(my_fd, my_buff, strlen(tab_str[i]));
		close(off_fd);
		close(my_fd);
		printf("TEST %2zu: ", i);
		if (off_ret != my_ret)
		{
			printf("\033[31m");
			printf("FAILURE\n");
			printf("\033[39m");
			printf("Returns are different:\n");
			printf("Official ret = %zd\n", off_ret);
			printf("My ret       = %zd\n", my_ret);
		}
		else
		{
			if (strcmp(off_buff, my_buff) != 0)
			{
				printf("\033[31m");
				printf("FAILURE\n");
				printf("\033[39m");
				printf("Buffers are different:\n");
				printf("Official buff = \"%s\"\n", off_buff);
				printf("My buff       = \"%s\"\n", my_buff);
			}
			else
			{
				printf("\033[32m");
				printf("SUCCESS\n");
				printf("\033[39m");
			}
		}
		i++;
	}
	success = 1;
	my_ret = ft_write(8, "ddsf", 4);
	errno_1 = errno;
	off_ret = write(8, "dsds", 4);
	errno_2 = errno;
	printf("TEST %2zu: ", i);
	if (off_ret != my_ret)
	{
		printf("\033[31m");
		printf("FAILURE\n");
		printf("\033[39m");
		printf("Returns are different:\n");
		printf("Official ret = %zd\n", off_ret);
		printf("My ret       = %zd\n", my_ret);
		success = 0;
	}
	if (errno_1 != errno_2)
	{
		printf("\033[31m");
		if (success)
			printf("FAILURE\n");
		printf("\033[39m");
		printf("Errno are different:\n");
		printf("Errno after ft_write = %d\n", errno_1);
		printf("Errno after write    = %d\n", errno_2);
		success = 0;
	}
	if (success)
	{
		printf("\033[32m");
		printf("SUCCESS\n");
		printf("\033[39m");
	}
	remove(off_file);
	remove(my_file);
}


int		main()
{
	test_ft_strlen();
	printf("\n");
	test_ft_strcpy();
	printf("\n");
	test_ft_strcmp();
	printf("\n");
	test_ft_write();
	return (0);
}