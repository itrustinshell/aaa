#include "../minishell.h"

/* Ottieni il percorso del comando */
char *get_cmdpath(char *cmd)
{
	char *path;
	char **splitted_path;
	char *finalpath;
	int i;
	int access_result;

	if (!cmd)
		return (NULL);
	path = getenv("PATH");
	if (!path)
		return (NULL);
	splitted_path = ft_split(path, ':');
	if (!splitted_path)
		return (NULL);
	i = 0;
	while (splitted_path[i])
	{
		finalpath = strjoin(splitted_path[i], "/");
		if (!finalpath)
		{
			free(splitted_path);
			return (NULL);
		}
		finalpath = strjoin(finalpath, cmd);
		if (!finalpath)
		{
			free(splitted_path);
			return (NULL);
		}
		access_result = access(finalpath, X_OK);
		if (access_result == 0)
		{
			free(splitted_path);
			return (finalpath);
		}
		free(finalpath);
		i++;
	}
	free(splitted_path);
	printf("NON HO TROVATO IL COMANDO!!!\n");
	return (NULL);
}

/* Crea un nuovo nodo t_cmd dalla matrice di comandi */
t_cmd *create_cmd(char **matrix)
{
	int			i;
	int			matrix_len;
	t_cmd	*cmd;

	if (!matrix || !matrix[0])
		return (NULL);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = strdup(matrix[0]);
	if (!cmd->cmd)
	{
		free(cmd);
		return (NULL);
	}
	matrix_len = matrixlen(matrix);
	cmd->args = (char **)malloc((matrix_len + 1) * sizeof(char *));
	if (!cmd->args)
	{
		free(cmd->cmd);
		free(cmd);
		return (NULL);
	}
	i = 0;
	while (i < matrix_len)
	{
		cmd->args[i] = strdup(matrix[i]);
		if (!cmd->args[i])
		{
			while (i > 0)
			{
				free(cmd->args[--i]);
			}
			free(cmd->args);
			free(cmd->cmd);
			free(cmd);
			return (NULL);
		}
		i++;
	}
	cmd->args[i] = NULL;
	cmd->next = NULL;
	return (cmd);
}
