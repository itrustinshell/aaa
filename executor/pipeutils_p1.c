#include "../minishell.h"

/*allocates the array of pipes*/
int	**pipesalloc(int cmdlist_len)
{
	int	i;
	int	**pipematrix;
	int	num_of_pipes;

	num_of_pipes = cmdlist_len - 1;
	pipematrix = (int **)malloc((num_of_pipes) * sizeof(int *));
	i = -1;
	while (++i < num_of_pipes)
		pipematrix[i] = (int *)malloc(2 * sizeof(int));
	i = -1;
	while (++i < num_of_pipes)
		pipe(pipematrix[i]);
	return (pipematrix);
}

/*read stdin from the pipe*/
void	piperead(int **pipematrix, int i)
{
	close(pipematrix[i - 1][WRITE_END]);
	dup2(pipematrix[i - 1][READ_END], STDIN_FILENO);
	close(pipematrix[i - 1][READ_END]);
}

/*write stdout in the pipe*/
void	pipewrite(int **pipematrix, int i)
{
	close(pipematrix[i][READ_END]);
	dup2(pipematrix[i][WRITE_END], STDOUT_FILENO);
	close(pipematrix[i][WRITE_END]);
}

/*close all pipe*/
void	pipeclose(int **pipematrix, int cmdlist_len)
{
	int	n;

	n = -1;
	while (++n < (cmdlist_len - 1))
	{
		close(pipematrix[n][READ_END]);
		close(pipematrix[n][WRITE_END]);
	}
}
