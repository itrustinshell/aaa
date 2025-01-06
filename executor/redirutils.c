#include "../minishell.h"

/*write in all output and append redirections*/
void	oa_redirwrite(t_redir *redirnode)
{
	int		fd;
	t_redir	*tmp_redirnode;

	if (!redirnode)
		return ;
	tmp_redirnode = redirnode;
	if (tmp_redirnode->type == OUTPUT_REDIRECTION)
	{
		fd = open(tmp_redirnode->file,
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (tmp_redirnode->type == APPEND_REDIRECTION)
	{
		fd = open(tmp_redirnode->file,
				O_WRONLY | O_CREAT | O_APPEND, 0666);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

/*open all output and append redirections*/
int	oa_rediropen(t_redir *redirlist)
{
	int		fd;
	int		output_append_exists;
	t_redir	*tmp_redirlist;

	output_append_exists = 0;
	tmp_redirlist = redirlist;
	while (tmp_redirlist)
	{
		if (tmp_redirlist->type == OUTPUT_REDIRECTION)
		{
			output_append_exists = 1;
			fd = open(tmp_redirlist->file,
					O_WRONLY | O_CREAT | O_TRUNC, 0666);
			close(fd);
		}
		if (tmp_redirlist->type == APPEND_REDIRECTION)
		{
			output_append_exists = 1;
			fd = open(tmp_redirlist->file,
					O_WRONLY | O_CREAT | O_APPEND, 0666);
			close(fd);
		}
		tmp_redirlist = tmp_redirlist->next;
	}
	return (output_append_exists);
}

/*find last occurrence indifferently among output or append redirections*/
t_redir	*oa_redirlast(t_redir *redirlist)
{
	t_redir	*ret;
	t_redir	*tmp;

	if (!redirlist)
		return (NULL);
	tmp = redirlist;
	ret = NULL;
	while (tmp)
	{
		if (tmp->type == OUTPUT_REDIRECTION || tmp->type == APPEND_REDIRECTION)
			ret = tmp;
		tmp = tmp->next;
	}
	return (ret);
}

/*finds last input redirections*/
t_redir	*i_redirlast(t_redir *redirlist)
{
	t_redir	*tmp_redirlist;
	t_redir	*ret;
	if (!redirlist)
		return (NULL);
	ret = NULL;
	tmp_redirlist = redirlist;
	while (tmp_redirlist)
	{
		if (tmp_redirlist->type == INPUT_REDIRECTION || tmp_redirlist->type == HEREDOC)
			ret = tmp_redirlist;
		tmp_redirlist = tmp_redirlist->next;
	}
	return (ret);
}
