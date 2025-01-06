#include "../minishell.h"

/*exec builtins or external cmd*/
void	ft_execve(t_cmd *tmp_cmdlist, t_env *genvlist)
{
	char	**envlist;
	printf("sono già entrato in execve\n");

	if (builtinex(tmp_cmdlist, &genvlist) == 1)
		return ;
	tmp_cmdlist->path = get_cmdpath(tmp_cmdlist->cmd);
	envlist = litoma(genvlist);
	execve(tmp_cmdlist->path, tmp_cmdlist->args, envlist);
}

/*fork along the pipes*/
void	pipefork(int **pipematrix, t_cmd *cmdlist, 
		int i, int cmdlist_len, t_env **env)
{
	int	pid;
	int	saved_stdout;
	int	n_heredoc;
	int	i_ret;
	t_cmd *tmp_cmdlist;
	if (!cmdlist)
	{
		printf("CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC....NON ESISTE\n");
	}
	else 
		printf("ESSISTEEEEEEEE\n");

	tmp_cmdlist = cmdlist;
	pid = fork();
	saved_stdout = dup(STDOUT_FILENO);
	if (pid == 0)
	{
		n_heredoc = 0;
		if (i > 0)
		{
			piperead(pipematrix, i);
			i_ret = ioa_redirops(tmp_cmdlist->redirlist, saved_stdout, &n_heredoc);
			printf("sono stati rilevati %d heredoc\n", n_heredoc);
			if (i_ret == 0)
			{
				printf("Last inputredir is an iredir, but the file doesnt exist.\n");
				exit(1);
			}
			else if (i_ret == 2)
				printf("NO iredr o heredoc found!!!\n");
			else if (i_ret == 3)
				printf("last inputredir is an iredir and it is OK\n");
			else if (i_ret == 4)
				printf("last inputredir is an HEREDOC\n");
		}
		if (tmp_cmdlist->next)
		{
			pipewrite(pipematrix, i);
			i_ret = ioa_redirops(tmp_cmdlist->redirlist, saved_stdout, &n_heredoc);
			printf("sono stati rilevati %d heredoc\n", n_heredoc);
			if (i_ret == 0)
			{
				printf("Last inputredir is an iredir, but the file doesnt exist.\n");
				exit(1);
			}
			else if (i_ret == 2)
				printf("NO iredr o heredoc found!!!\n");
			else if (i_ret == 3)
				printf("last inputredir is an iredir and it is OK\n");
			else if (i_ret == 4)
				printf("last inputredir is an HEREDOC\n");
		}
		if (n_heredoc)
			printf("Ora creo le heredoc! E ridirigo output\n");
		pipeclose(pipematrix, cmdlist_len);
		ft_execve(tmp_cmdlist, *env);
		exit(1);
	}
}
