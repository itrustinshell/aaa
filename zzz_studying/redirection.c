#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "../minishell.h"

int ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int main(int argc, char **argv)
{
	char	*path;
	char	*text;
	int		fd;

	path = argv[1];
	
	text = argv[2];

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0466);

	write(fd, text, ft_strlen(text));



}
