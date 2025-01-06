#include "../minishell.h"

void	printallheredoclists(t_cmd *cmd)
{
	t_cmd		*tmp_cmdlist;
	t_redir		*tmp_redir;
	t_heredoc	*tmp_heredoc;

	tmp_cmdlist = cmd;
	//printf("sto per stampare la lista di heredoc: %s\n", tmp_cmdlist->cmd);
	if (tmp_cmdlist)
	{
		while (tmp_cmdlist)
		{
			if (tmp_cmdlist->redirlist)
				tmp_redir = tmp_cmdlist->redirlist;
			while (tmp_redir && tmp_redir->type != HEREDOC)
				tmp_redir = tmp_redir->next;
			if(tmp_redir && tmp_redir->heredoclist)
			{
				//printf("questa è la lista con delimiter: %s\n", tmp_redir->delimiter);
				tmp_heredoc = tmp_redir->heredoclist;
				while (tmp_heredoc)
				{
					printf("- %s", tmp_heredoc->input);
					tmp_heredoc = tmp_heredoc->next;
				}
				tmp_redir = tmp_redir->next;
			}
			tmp_cmdlist = tmp_cmdlist->next;
		}
	}
}

int	count_heredoc(t_cmd *cmd)
{
	t_cmd	*tmp_cmd;
	int		n_heredoc;
	t_redir	*tmp_redir;

	if (!cmd)
		return (0);
	tmp_cmd = cmd;
	n_heredoc = 0;
	while (tmp_cmd)
	{
		if (tmp_cmd->redirlist)
		{
			tmp_redir = tmp_cmd->redirlist;
			while (tmp_redir)
			{
				if (tmp_redir->type == HEREDOC)
					n_heredoc = n_heredoc + 1;
				tmp_redir = tmp_redir->next;
			}
		}
		tmp_cmd = tmp_cmd->next;
	}
	return (n_heredoc);
}
/*
TEST:
ls | ls < dd << d | ls < e > s | ls << d << d < d << f | ls < k << l < kkk | ls << l << p < a
ls << d << z| grep a < a << we < a | sort << haha < a << pp < a
*/