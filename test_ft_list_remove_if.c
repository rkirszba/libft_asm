#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct	s_list
{
	void			*data;
	struct s_list	*next;
}				t_list;

extern void	ft_list_push_front(t_list **elem, void *data);

void	free_function(void *str)
{
	free(str);
}

void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *))
{
	t_list	*prev_cursor;
	t_list	*cursor;
	t_list	*tmp;

	prev_cursor = NULL;
	cursor = *begin_list;
	while (cursor)
	{
		if (!cmp(cursor->data, data_ref))
		{
			tmp = cursor;
			if (prev_cursor == NULL)
				*begin_list = (*begin_list)->next;
			else
				prev_cursor->next = cursor->next;
			cursor = cursor->next;
			free_fct(tmp->data);
			free(tmp);
			continue ;
		}
		prev_cursor = cursor;
		cursor = cursor->next;
	}
}


int		main()
{
	char	tab[10][2] = {
		"0",
		"1",
		"2",
		"3",
		"3",
		"3",
		"6",
		"7",
		"8",
		"9"
	};
	t_list	*head;
	int		i;

	head = NULL;
	i = 10;
	while (--i >= 0)
		ft_list_push_front(&head, strdup(tab[i]));
	ft_list_remove_if(&head, "3", &strcmp, &free_function);
	while (head)
	{
		printf("%s\n", head->data);
		head = head->next;
	}
	return (0);
}