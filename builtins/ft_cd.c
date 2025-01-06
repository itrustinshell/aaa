
#include "../minishell.h"

//DA IMPLEMENTARE
int	ft_cd(char **argv)
{
	char	*cwdpath;
	char	*strmaps;
	char	*str;

	(void)str;
	(void)cwdpath;
	strmaps = argv[1];
	cwdpath = getcwd(NULL, 0);
	if (!strmaps)
		return (0);
	chdir(strmaps);
	str = getcwd(NULL, 0);
	return (1);
}
