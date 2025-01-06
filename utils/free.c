#include "../minishell.h"

void	ft_free_n_matrix(char **matrix, int n)
{
	int	j;

	j = 0;
	while (j < n)
	{
		free(matrix[j]);
		j++;
	}
	free(matrix);
}

void	ft_freematrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}

void	ft_freelist(t_env *envlist)
{
	t_env	*tmp_list;
	t_env	*saved_tmplist;

	if (!envlist)
		return;
	tmp_list = envlist;
	while(tmp_list->next)
	{
		saved_tmplist = tmp_list;
		tmp_list = tmp_list->next;
		free(saved_tmplist->name);
		free(saved_tmplist->value);
		free(saved_tmplist);
	}
	free(tmp_list->name);
	free(tmp_list->value);
	free(tmp_list);
}

void	free_cmd(t_cmd *cmd) //solo quando è singolo comando....uindi non frea le liste di comandi....non fria i next...aaa dovrebbe friare la lista di redir perchè è fissa per  ogni comando...da implementare
{
	if (cmd)
	{
		if (cmd->cmd)
			free(cmd->cmd);
		if (cmd->args)
			ft_freematrix(cmd->args);
		if (cmd->path)
			free(cmd->path);
		free(cmd);
	}
}