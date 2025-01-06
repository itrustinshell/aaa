#include "../minishell.h"

/*execute pipes
stats all forks in a while, then the father waits.
*/
int	pipex(t_cmd *cmdlist, int cmdlist_len, int **pipematrix, t_env **env)
{
	int			i;
	t_cmd	*tmp_cmdlist;

	tmp_cmdlist = cmdlist;
	if (tmp_cmdlist->redirlist)
		printf("EEEEEEEEEEEEEEEEE.......non esiste\n");
	else
		printf("LAAA LISTAAA ESISTEEEEE\n");


	if (!tmp_cmdlist)
		return (0);
	i = -1;
	while (++i < cmdlist_len)
	{
		if (i > 0)
			tmp_cmdlist = tmp_cmdlist->next;
		pipefork(pipematrix, tmp_cmdlist, i, cmdlist_len, env);
	}
	pipeclose(pipematrix, cmdlist_len);
	i = 0;
	while (i < cmdlist_len)
	{
		wait(NULL);
		i++;
	}
	return (0);
}

/*execute builtins*/
int	builtinex(t_cmd *cmd, t_env **env)
{
	int	a;

	if (strcmp(cmd->cmd, "echo") == 0)
	{
		a = 0;
		while (cmd->args[a])
			a++;
		ft_echo(a, cmd->args);
		return (1);
	}
	else if (strcmp(cmd->cmd, "pwd") == 0)
		return (ft_pwd());
	else if (strcmp(cmd->cmd, "export") == 0)
	{
		if (exportcheck(cmd->args) == 1)
			ft_export(cmd->args[1], env);
	}
	else if (strcmp(cmd->cmd, "cd") == 0)
		return (ft_cd(cmd->args));
	else if (strcmp(cmd->cmd, "env") == 0)
		return (ft_env(*env));
	else if (strcmp(cmd->cmd, "exit") == 0)
	{
		ft_exit();
		return (1);
	}
	return (0);
}

/*execute single command*/
void	cmdex(t_cmd *cmd, t_env **env)
{
	pid_t	pid;
	int		status;

	if (builtinex(cmd, env))
		return ;
	cmd->path = get_cmdpath(cmd->cmd);
	pid = fork();
	if (pid == 0)
	{
		execve(cmd->path, cmd->args, NULL);
		exit(1);
	}
	waitpid(pid, &status, 0);
}

void heredoc_prompt(char **inputstr)
{
	size_t len;
	len = 0;

	//*inputstr = NULL;
	
	printf(">: ");
	getline(inputstr, &len, stdin); //free di inputstr fatto!

}

void	heredocinit(t_heredoc *node)
{
	if (node)
	{
		node->input = NULL;
		node->next = NULL;
	}
}

t_heredoc *create_heredocnode(char *inputstr)
{
	t_heredoc	*node;

	if(!inputstr)
		return (NULL);
	node = (t_heredoc *)malloc(sizeof(t_heredoc));
	heredocinit(node);
	node->input = strdup(inputstr);
	return (node);

}

t_heredoc	*last_heredocnode(t_heredoc *list)
{
	t_heredoc	*current;

	current = list;
	while (current->next != NULL)
		current = current->next;
	return (current);
}

void	listappend_heredoc(t_heredoc *node, t_heredoc **list)
{
	t_heredoc	*last_node;

	if (*list == NULL)
	{
		*list = node;
		(*list)->next = NULL;
	}
	else
	{
		last_node = last_heredocnode(*list);
		last_node->next = node;
		node->next = NULL;
	}
}

void	build_heredoclist(char *inputstr, t_heredoc **heredoclist)
{
	t_heredoc	*node;

	(void)inputstr;
	if (!heredoclist)
		printf("la lista è nulla\n");
	node = create_heredocnode(inputstr);
	listappend_heredoc(node, heredoclist);

}


void	heredoc(t_cmd *cmd, int n_heredoc)
{
	int		k;
	char	*inputstr;
	size_t	len;
	int		j;
	t_cmd *tmp_cmdlist;
	t_redir *tmp_redirlist;

	

	tmp_cmdlist = cmd;

	len = 0;

	if (!n_heredoc)
		return;
	while (tmp_cmdlist)
	{
		tmp_redirlist = tmp_cmdlist->redirlist;
		while (tmp_redirlist && tmp_redirlist->type != HEREDOC)
			tmp_redirlist = tmp_redirlist->next;
		if(tmp_redirlist)
		{
			//do the operation with this delimiter
			//...
			printf("inizio la comparazione e la presa di input\n");
			
			while (1)
			{
				//heredoc_prompt(&inputstr);
				printf(">: ");
				getline(&inputstr, &len, stdin);
				
				int j = 0;
				while (inputstr[j] != '\n')
				{
					j++;
				}
				inputstr[j] = '\0';
				printf("you inserted: %s. Remember the current delimiter is: %s\n", inputstr,tmp_redirlist->delimiter );
				if (strcmp(inputstr,  tmp_redirlist->delimiter) == 0)
					break;
				inputstr[j] = '\n';

				build_heredoclist(inputstr, &(tmp_redirlist->heredoclist));

			}
			tmp_redirlist = tmp_redirlist->next;
		}
		tmp_cmdlist = tmp_cmdlist->next;
	}
}

/*execute cmdlist*/
void	executor(t_cmd *cmdlist, t_env **env)
{
	int	cmdlist_len;
	int	**pipematrix;
	int	n_heredoc;
	if (cmdlist->redirlist)
		printf("in ecxecutor   esiste una lista\n");
	//printlist(cmdlist);
	n_heredoc = count_heredoc(cmdlist);
	printf("n_heredoc: %d\n", n_heredoc);
	heredoc(cmdlist, n_heredoc);
	printallheredoclists(cmdlist, n_heredoc);

	cmdlist_len = listlen(cmdlist);
	if (cmdlist_len > 1)
	{
		pipematrix = pipesalloc(cmdlist_len);
		pipex(cmdlist, cmdlist_len, pipematrix, env);
	}
	else
		cmdex(cmdlist, env);
}
