#include "../minishell.h"

int	ft_echo(int argc, char **argv)
{
	int	i;

	if (strcmp(argv[1], "-n") == 0)
	{
		i = 2;
		while (i < argc - 1)
		{
			printf("%s ", argv[i]);
			i++;
		}
		printf("%s", argv[i]);
	}
	else
	{
		i = 1;
		while (i < argc - 1)
		{
			printf("%s ", argv[i]);
			i++;
		}
		printf("%s\n", argv[i]);
	}
	return (1);
}
