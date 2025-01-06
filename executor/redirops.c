#include "../minishell.h"

/*operations with output and append redirections*/
void	oa_redirops(t_redir *redirlist)
{
	t_redir	*redirnode;

	redirnode = NULL;
	if (!redirlist)
		return ;
	if (oa_rediropen(redirlist) == 0)
		return ;
	redirnode = oa_redirlast(redirlist);
	if (!redirnode)
		return ;
	oa_redirwrite(redirnode);
}

/*If exist an input redirection, then the indicated
file is checked with "access". If it exists, it is
open, and the input is redirected to his fd.
RETURN: returns 0 only if user indicates a file that 
doesn't exist. In all the other cases it returns 1,
even if there are no redirection.
Indeed, if there is no input redirection, no file is 
opened and the stdin just is not redirect to any fd.
*/
int	i_redirops(t_redir *redirlist, int saved_stdout, int *n_heredoc)
{
	int		fd;
	t_redir	*latest_input_redir;
	int		ret;
	printf("sono in i_redirops\n");
	ret = 1;
	if (!redirlist)
	{
		printf("AAAAAAAA NON ESISTEEEE\n");
		return (ret);
	}
	latest_input_redir = i_redirlast(redirlist);
	if (!latest_input_redir)
		return (2);
	if (latest_input_redir->type == INPUT_REDIRECTION)
	{
		printf("l'ultimo input è un input-redirections\n");
		ret = 3;
		if (access(latest_input_redir->file, F_OK) == 0)
		{
			fd = open(latest_input_redir->file, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else
		{	
			dup2(saved_stdout, STDOUT_FILENO);
			printf("ERROREEEEEEEEE\n");
			ret = 0;
		}
	}
	else if(latest_input_redir->type == HEREDOC)
	{
		int fdpipe[2];
		pipe(fdpipe);
        if (latest_input_redir->heredoclist) 
		{
            t_heredoc *current = latest_input_redir->heredoclist;
            while (current) 
			{
                write(fdpipe[1], current->input, strlen(current->input));
                current = current->next;
            }
            close(fdpipe[1]); // Chiudi il lato di scrittura della pipe
        }
        dup2(fdpipe[0], STDIN_FILENO);
        close(fdpipe[0]); // Chiudi il lato di lettura della pipe
		return (4);
	}
	return (ret);
}

/*the whole input-output-append operations

*/
int	ioa_redirops(t_redir *redirlist, int saved_stdout, int *n_heredoc)
{
	int	i_ret;

	if (!redirlist)
		printf("BBBBBBBBBBBBBBBBBB non esisteeee\n");
	i_ret = i_redirops(redirlist, saved_stdout, n_heredoc);
	if (i_ret == 0)
	{
		// printf("The symbol of iredi was found...but the file doesnt exist.\n");
		return (0);
	}
	// else
	// {
	// 	if (i_ret == 2)
	// 		printf("NO iredr o heredoc found!!!\n");
	// 	if (i_ret == 3)
	// 		printf("last inputredir is an iredir\n");
	// 	if (i_ret == 4)
	// 		printf("last inputredir is an HEREDOC\n");
	// }
	oa_redirops(redirlist);
	return (i_ret);
}
