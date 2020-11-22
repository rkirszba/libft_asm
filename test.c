#include <stdio.h>

int	main(void)
{
	char 	tab[8][2] = {
		{"a"},
		{"b"}
	};
	int	i = 0;
	while (tab[i])
	{
		printf("%d", i);
		i++;
	}
	return (0);
}