#include "../minishell.h"

/* Inizializza la struttura t_cmd */
void cmdinit(t_cmd *cmd)
{
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->path = NULL;
	cmd->next = NULL;
	cmd->redirlist = NULL;
}

/* Inizializza la struttura t_redir */
void redirinit(t_redir *node)
{
	node->type = 0;
    node->file = NULL;
    node->delimiter = NULL;
    node->heredoclist = NULL;
    node->next = NULL;
}