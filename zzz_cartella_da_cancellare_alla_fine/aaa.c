


void cmd_before_single_outredirection(char **matrix)
{
	t_cmd	*cmd;
	int			i;
	int			fd;

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
	i++;
	fd = open(matrix[i], O_WRONLY | O_CREAT | O_TRUNC, 0466); //TODO aprire il file dato in path assoluto e relativo
	
	int pid = fork();

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

