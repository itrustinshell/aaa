#include "minishell.h"

/*alloca gli argomenti del comando*/
void	argsalloc(t_cmd *cmdlist, char **tokenmatrix, int n_args, int i)
{
	int		t;
	t_cmd	*lastcmd;;
	
	lastcmd = last_cmdnode(cmdlist);

	if (n_args)
	{
		lastcmd->args = (char **)malloc((n_args + 1) * sizeof(char *));
		t = 0;
		while(t < n_args)
		{
			lastcmd->args[t] = strdup(tokenmatrix[i + t]);
			t++;
		}
		lastcmd->args[t] = NULL;
	}
}

/*alloca la lista di redirection per il comando specificato*/
void	redirlistalloc(t_cmd *cmdlist, char **tokenmatrix, int i)
{
	t_redir	*redirnode;

	if (strcmp(tokenmatrix[i], ">") == 0 || strcmp(tokenmatrix[i], "<") == 0 || strcmp(tokenmatrix[i], ">>") == 0 || strcmp(tokenmatrix[i], "<<") == 0)
	{
		redirnode = (t_redir *)malloc(sizeof(t_redir));
		redirinit(redirnode);
		if ((strcmp(tokenmatrix[i], ">") == 0))
			redirnode->type = OUTPUT_REDIRECTION;
		if ((strcmp(tokenmatrix[i], "<") == 0))
			redirnode->type = INPUT_REDIRECTION;
		if ((strcmp(tokenmatrix[i], ">>") == 0))
			redirnode->type = APPEND_REDIRECTION;
		if ((strcmp(tokenmatrix[i], "<<") == 0))
			redirnode->type = HEREDOC;
		i++;
		if (redirnode->type == OUTPUT_REDIRECTION || redirnode->type == INPUT_REDIRECTION || redirnode->type == APPEND_REDIRECTION)
			redirnode->file = tokenmatrix[i];
		else
			redirnode->delimiter = tokenmatrix[i];
		listappend_redir(redirnode, &last_cmdnode(cmdlist)->redirlist);
	}
}

t_cmd	*parsing(char **tokenmatrix)
{
	int			i;
	int			n_args;
	t_cmd		*cmd;
	t_cmd		*cmdlist;

	cmdlist = NULL;
	i = 0;
	while (tokenmatrix[i] != NULL)
	{	
		cmd = (t_cmd *)malloc(sizeof(t_cmd));
		cmdinit(cmd);
		listappend_command(cmd, &cmdlist);
		last_cmdnode(cmdlist)->cmd = strdup(tokenmatrix[i]);
		n_args = 0;
		while (tokenmatrix[i + n_args] &&
			strcmp(tokenmatrix[i + n_args], ">") != 0 &&
			strcmp(tokenmatrix[i + n_args], "<") != 0 &&
			strcmp(tokenmatrix[i + n_args], ">>") != 0 &&
			strcmp(tokenmatrix[i + n_args], "<<") != 0 &&
			tokenmatrix[i + n_args][0] != PIPE)
			n_args++;
		argsalloc(cmdlist, tokenmatrix, n_args, i);
		i = i + n_args;
		while (tokenmatrix[i] && tokenmatrix[i][0] != PIPE)
		{
			redirlistalloc(cmdlist, tokenmatrix, i);
			i++;
		}
		if (!tokenmatrix[i])
			break;
		i++;
	}
	return (cmdlist);
}
