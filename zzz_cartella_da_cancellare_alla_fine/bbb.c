

int check_redirection_symbol(char **tokenmatrix)
{
	int	i;

	i = 0;
	while (tokenmatrix[i])
	{
		if (tokenmatrix[i][0] != OUTPUT_REDIRECTION)
			i++;
		else
		{
			//printf("there is a pipe\n");
			return (THERE_IS_A_REDIRECTION);

		}
	}
	return (THERE_IS_NOT_A_REDIRECTION);
}

t_cmd *get_cmd(char **matrix)
{
	t_cmd	*cmd;
	int			i;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->cmd = strdup(matrix[0]);
	cmd->path = get_cmdpath(cmd->cmd);
	i = 0;
	while (matrix[i][0] != OUTPUT_REDIRECTION)
		i++;
	cmd->args = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	while (matrix[i][0] != OUTPUT_REDIRECTION)
	{
		cmd->args[i] = strdup(matrix[i]);
		i++;
	}
	cmd->args[i] = NULL;
	return (cmd);
}

void single_outredirection(char **matrix)
{
	int			i;
	int			fd;
	int			pid;
	char		*file;
	t_cmd	*cmd;

	cmd = get_cmd(matrix);
	while (matrix[i][0] != OUTPUT_REDIRECTION)
		i++;
	i++;
	file = matrix[i];
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0466); //TODO aprire il file dato in path assoluto e relativo
	
	pid = fork();

	if (pid == 0)
	{
		
		dup2(fd, STDOUT_FILENO);
		close(fd);
		execve(cmd->path, cmd->args, NULL);
	}
	else
	{
		close(fd);
		wait(NULL);

	}			
}

