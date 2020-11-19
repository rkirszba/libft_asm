#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libc.h>

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

int		main()
{
	test_ft_strlen();
	printf("\n");
	test_ft_strcpy();
	printf("\n");
	test_ft_strcmp();
	return (0);
}