#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libc.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/errno.h>

#define	NB_STRINGS			11
#define MAX_STRING_LEN		100
#define	READ_SIZE			14

#define NB_ATOI_BASE_TEST	14
#define NB_SORT_LIST_TEST	11
#define NB_REMOVE_LIST_TEST	9

typedef struct	s_test_atoi_base
{
	char	*str;
	char	*base;
	int		expected_result;	
}				t_test_atoi_base;

typedef struct	s_list
{
	void			*data;
	struct s_list	*next;

}				t_list;



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
extern ssize_t	ft_read(int fildes, void *buf, size_t nbyte);
extern char 	*ft_strdup(const char *s1);
extern int		ft_atoi_base(char *str, char *base);
extern void		ft_list_push_front(t_list **begin_list, void *data);
extern int		ft_list_size(t_list *begin_list);
extern void		ft_list_sort(t_list **begin_list, int (*cmp)());
extern void		ft_list_remove_if(t_list **begin_list, void *data_ref,
				int (*cmp)(), void (*free_fct)(void *));



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
		read(off_fd, off_buff, MAX_STRING_LEN);
		read(my_fd, my_buff, MAX_STRING_LEN);
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

void	test_ft_read()
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
	printf("------- Tests on ft_read  --------\n\n");
	while (i < NB_STRINGS)
	{
		off_fd = open(off_file, O_RDWR | O_CREAT, S_IRWXU);
		my_fd = open(my_file, O_RDWR | O_CREAT, S_IRWXU);
		write(off_fd, tab_str[i], strlen(tab_str[i]));
		write(my_fd, tab_str[i], strlen(tab_str[i]));
		close(off_fd);
		close(my_fd);
		off_fd = open(off_file, O_RDONLY);
		my_fd = open(my_file, O_RDONLY);
		bzero(off_buff, MAX_STRING_LEN);
		bzero(my_buff, MAX_STRING_LEN);
		off_ret = read(off_fd, off_buff, READ_SIZE);
		my_ret = ft_read(my_fd, my_buff, READ_SIZE);
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
	my_ret = ft_read(8, my_buff, 4);
	errno_1 = errno;
	off_ret = write(8, off_buff, 4);
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
		printf("Errno after ft_read = %d\n", errno_1);
		printf("Errno after read    = %d\n", errno_2);
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

void	test_ft_strdup(void)
{
	size_t	i;
	char	*off_str;
	char	*my_str;
	
	i = 0;
	printf("------- Tests on ft_strdup --------\n\n");
	while (i < NB_STRINGS)
	{
		off_str = strdup(tab_str[i]);
		my_str = ft_strdup(tab_str[i]);
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
		else if (my_str == tab_str[i])
		{
			printf("\033[31m");
			printf("FAILURE\n");
			printf("\033[39m");
			printf("Cheater, you used the same string !:\n");
		}
		else
		{
			printf("\033[32m");
			printf("SUCCESS\n");
			printf("\033[39m");
		}
		free(off_str);
		free(my_str);
		i++;
	}
}

void	init_atoi_base_tab(t_test_atoi_base *tab)
{
	tab[0].str = "aaaaaaaa";
	tab[0].base = "";
	tab[0].expected_result = 0;
	tab[1].str = "aaaaaaa";
	tab[1].base = "a";
	tab[1].expected_result = 0;
	tab[2].str = "0";
	tab[2].base = "0123456789";
	tab[2].expected_result = 0;
	tab[3].str = "-1";
	tab[3].base = "0123456789";
	tab[3].expected_result = -1;
	tab[4].str = "+1";
	tab[4].base = "0123456789";
	tab[4].expected_result =  1;
	tab[5].str = "2147483647";
	tab[5].base = "0123456789";
	tab[5].expected_result = 2147483647;
	tab[6].str = "7fffffff";
	tab[6].base = "0123456789abcdef";
	tab[6].expected_result = 2147483647;
	tab[6].str = "-ffffffff";
	tab[6].base = "0123456789abcdef";
	tab[6].expected_result = 1;
	tab[7].str = "-80000000";
	tab[7].base = "0123456789abcdef";
	tab[7].expected_result = -2147483648;
	tab[8].str = "12312";
	tab[8].base = "00123";
	tab[8].expected_result = 0;
	tab[9].str = "12312";
	tab[9].base = "01230";
	tab[9].expected_result = 0;
	tab[10].str = "123";
	tab[10].base = "-01230";
	tab[10].expected_result = 0;
	tab[11].str = "123";
	tab[11].base = "01230+";
	tab[11].expected_result = 0;
	tab[12].str = "1234";
	tab[12].base = "0123";
	tab[12].expected_result = 0;
	tab[13].str = "1111111111111111111111111111111";
	tab[13].base = "01";
	tab[13].expected_result = 2147483647;
	tab[13].str = "11111111111111111111111111111111";
	tab[13].base = "01";
	tab[13].expected_result = -1;	
}

void	test_ft_atoi_base(void)
{
	size_t					i;
	t_test_atoi_base		tab[NB_ATOI_BASE_TEST];
	int						result;
	
	init_atoi_base_tab(tab);
	i = 0;
	printf("------- Tests on ft_atoi_base --------\n\n");
	while (i < NB_ATOI_BASE_TEST)
	{
		result = ft_atoi_base(tab[i].str, tab[i].base);
		printf("TEST %2zu: ", i);
		if (result != tab[i].expected_result)
		{
			printf("\033[31m");
			printf("FAILURE\n");
			printf("\033[39m");
			printf("Results are different:\n");
			printf("Expected result = %d\n", tab[i].expected_result);
			printf("My result       = %d\n", result);
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

void	test_ft_list_push_front(void)
{
	t_list	*begin_list;
	t_list	*curs;
	char	*off_string = "I think it is working!";
	char	*my_string;
	char	*tmp;
	size_t	len;

	begin_list = NULL;
	ft_list_push_front(&begin_list, "working!");
	ft_list_push_front(&begin_list, "is ");
	ft_list_push_front(&begin_list, "it ");
	ft_list_push_front(&begin_list, "think ");
	ft_list_push_front(&begin_list, "I ");
	my_string = malloc(1);
	my_string[0] = '\0';
	curs = begin_list;
	while (curs)
	{
		len = strlen(my_string);
		tmp = my_string;
		my_string = malloc(strlen(my_string) + strlen(curs->data) + 1);
		my_string = strcpy(my_string, tmp);
		free(tmp);
		strcat(my_string, curs->data);
		curs = curs->next;
	}
	printf("------- Tests on ft_list_push_front --------\n\n");
	printf("TEST 0: ");
	if (strcmp(off_string, my_string) != 0)
	{
		printf("\033[31m");
		printf("FAILURE\n");
		printf("\033[39m");
		printf("Strings are different:\n");
		printf("Official string = \"%s\"\n", off_string);
		printf("My string       = \"%s\"\n", my_string);
	}
	else
	{
		printf("\033[32m");
		printf("SUCCESS\n");
		printf("\033[39m");
	}
}


void	test_ft_list_size(void)
{
	t_list	*elem;
	int		off_size;
	int		my_size;

	elem = NULL;
	off_size = -1;

	printf("------- Tests on ft_list_size --------\n\n");
	while (++off_size < 10)
	{
		my_size = ft_list_size(elem);
		printf("TEST %2d: ", off_size);
		if (off_size != my_size)
		{
			printf("\033[31m");
			printf("FAILURE\n");
			printf("\033[39m");
			printf("Sizes are different:\n");
			printf("Official size = %d\n", off_size);
			printf("My size       = %d\n", my_size);
		}
		else
		{
			printf("\033[32m");
			printf("SUCCESS\n");
			printf("\033[39m");
		}
		ft_list_push_front(&elem, NULL);
	}
}

int		get_test_len(char tab[11][2])
{
	int		i;

	i = 0;
	while (tab[i][0])
		i++;
	return (i);
}


void	test_ft_list_sort(void)
{
	char	tab[NB_SORT_LIST_TEST][10][2] = {
		{"\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0"},
		{"0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0"},
		{"0", "1", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0"},
		{"1", "0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0"},
		{"1", "0", "2", "\0", "\0", "\0", "\0", "\0", "\0", "\0"},
		{"0", "1", "3", "2", "\0", "\0", "\0", "\0", "\0", "\0"},
		{"0", "2", "1", "3", "\0", "\0", "\0", "\0", "\0", "\0"},
		{"5", "0", "1", "2", "3", "4", "\0", "\0", "\0", "\0"},
		{"1", "0", "3", "2", "5", "4", "7", "6", "\0", "\0"},
		{"8", "7", "6", "5", "4", "3", "2", "0", "1", "\0"},
		{"8", "7", "6", "5", "4", "3", "2", "1", "0", "\0"},

	};
	t_list	*begin_tree;
	t_list	*cursor;
	int		test_len;
	int		i;
	int		j;
	int		k;
	int		success;

	i = -1;
	printf("------- Tests on ft_list_sort --------\n\n");
	while (++i < NB_SORT_LIST_TEST)
	{
		success = 1;
		printf("TEST %2d: ", i);
		begin_tree = NULL;
		test_len = get_test_len(tab[i]);
		j = test_len;
		while (--j >= 0)
			ft_list_push_front(&begin_tree, tab[i][j]);
		ft_list_sort(&begin_tree, &strcmp);
		cursor = begin_tree;
		while (++j < test_len)
		{
			if ((char)(j + 0x30) != ((char*)(cursor->data))[0])
			{
				printf("\033[31m");
				printf("FAILURE\n");
				printf("\033[39m");
				printf("List is not sorted:\n");
				printf("Expected list = ");
				k = -1;
				while (++k < test_len)
					printf("%d ", k);
				printf("\n");
				printf("My list       = ");
				while (begin_tree)
				{
					printf("%s ", begin_tree->data);
					begin_tree = begin_tree->next;
				}
				printf("\n");
				success = 0;
				break ;
			}
			cursor = cursor->next;
		}
		if (success == 1)
		{
			printf("\033[32m");
			printf("SUCCESS\n");
			printf("\033[39m");
		}
	}
}

void	test_ft_list_remove_if(void)
{
	char	tab[NB_REMOVE_LIST_TEST * 3][11][2] = {
		{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "\0"},
		{"1", "2", "3", "4", "5", "6", "7", "8", "9", "\0"},
		{"0", "\0"},
		{"0", "0", "2", "3", "4", "5", "6", "7", "8", "9", "\0"},
		{"2", "3", "4", "5", "6", "7", "8", "9", "\0"},
		{"0", "\0"},
		{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "\0"},
		{"0", "2", "3", "4", "5", "6", "7", "8", "9", "\0"},
		{"1", "\0"},
		{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "\0"},
		{"0", "1", "2", "3", "4", "5", "6", "7", "8", "\0"},
		{"9", "\0"},
		{"0", "1", "2", "3", "4", "5", "6", "7", "9", "9", "\0"},
		{"0", "1", "2", "3", "4", "5", "6", "7", "\0"},
		{"9", "\0"},
		{"0", "1", "2", "3", "4", "0", "0", "7", "8", "0", "\0"},
		{"1", "2", "3", "4", "7", "8", "\0"},
		{"0", "\0"},
		{"0", "1", "2", "3", "4", "5", "6", "7", "8", "\0"},
		{"0", "1", "2", "3", "4", "5", "6", "7", "8", "\0"},
		{"a", "\0"},
		{"0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "\0"},
		{"\0"},
		{"0", "\0"},
		{"\0"},
		{"\0"},
		{"1", "\0"}, 
	};
	t_list	*head;
	t_list	*cursor;
	int		i;
	int		j;
	int		success;

	i = -1;
	printf("------- Tests on ft_list_remove_if --------\n\n");
	while (++i < NB_REMOVE_LIST_TEST)
	{
		success =1;
		head = NULL;
		j = get_test_len(tab[i * 3]);
		while (--j >= 0)
			ft_list_push_front(&head, strdup(tab[i * 3][j]));
		ft_list_remove_if(&head, tab[i * 3 + 2], &strcmp, &free);
		printf("TEST %2d: ", i);
		cursor = head;
		while (tab[i * 3 + 1][++j][0])
		{
			if (strcmp(tab[i * 3 + 1][j], cursor->data) != 0)
			{
				printf("\033[31m");
				printf("FAILURE\n");
				printf("\033[39m");
				printf("Expected list = ");
				j = -1;
				while (tab[i * 3 + 1][++j][0])
		 			printf("%s ", tab[i * 3 + 1][j]);
				printf("\n");
				printf("My list       = ");
				while (head)
				{
					printf("%s ", head->data);
					head = head->next;
				}
				printf("\n");
				success = 0;
				break ;
			}
			cursor = cursor->next;
		}
		if (success == 1)
		{
			printf("\033[32m");
			printf("SUCCESS\n");
			printf("\033[39m");
		}
	}
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
	printf("\n");
	test_ft_read();
	printf("\n");
	test_ft_strdup();
	printf("\n");
	test_ft_atoi_base();
	printf("\n");
	test_ft_list_push_front();
	printf("\n");
	test_ft_list_size();
	printf("\n");
	test_ft_list_sort();
	printf("\n");
	test_ft_list_remove_if();
	return (0);
}