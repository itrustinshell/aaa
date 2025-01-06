#include "../minishell.h"

int	ft_pwd(void)
{
	char	*cwd_buffer;

	cwd_buffer = NULL;
	cwd_buffer = getcwd(NULL, 0);
	printf("%s\n", cwd_buffer);
	free(cwd_buffer);
	return (1);
}
