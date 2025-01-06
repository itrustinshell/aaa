#include "../minishell.h"

t_env	*create_lenvnode(char *str)
{
	t_env	*new;
	char	**splittedstr;

	new = NULL;
	splittedstr = NULL;
	splittedstr = ft_split(str, '=');
	if (!splittedstr)
		return (NULL);
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
	{
		return (NULL);
	}
	init_envnode(new);
	new->name = strdup(splittedstr[0]);
	new->value = strdup(splittedstr[1]);
	return (new);
}

void	init_envnode(t_env *env)
{
	if (!env)
		return ;
	env->name = NULL;
	env->value = NULL;
	env->prev = NULL;
	env->next = NULL;
}

t_env	*last_envlist(t_env *envlist)
{
	t_env	*current;

	current = NULL;
	current = envlist;
	while (current->next != NULL)
		current = current->next;
	return (current);
}

void	envlist_append(t_env *node, t_env **list)
{
	t_env	*last_node;

	if (!node)
		return ;
	last_node = NULL;
	if (*list == NULL)
	{
		*list = node;
		(*list)->next = NULL;
		(*list)->prev = NULL;
	}
	else
	{
		last_node = last_envlist(*list);
		node->prev = last_node;
		last_node->next = node;
		node->next = NULL;
	}
}

int	envlist_len(t_env *list)
{
	int		i;
	t_env	*current;

	if (list == NULL)
		return (0);
	current = list;
	i = 0;
	while (current->next)
	{
		current = current->next;
		i++;
	}
	i++;
	return (i);
}

/*list to matrix*/
char	**litoma(t_env *envlist)
{
	int		lenlist;
	t_env	*tmp_envlist;
	char	**env_matrix;
	int		len_name;
	int		len_value;
	int		i;
	int		n;
	int		m;

	tmp_envlist = envlist;
	lenlist = envlist_len(tmp_envlist);
	env_matrix = (char **)malloc((lenlist + 1) * sizeof(char *));
	if (!env_matrix)
		return (NULL);
	i = 0;
	while (tmp_envlist)
	{
		len_name = ft_strlen(tmp_envlist->name);
		len_value = ft_strlen(tmp_envlist->value);
		env_matrix[i] = (char *)malloc((len_name + len_value + 2)
				* sizeof(char));
		if (!env_matrix[i])
			return (NULL);
		n = 0;
		m = 0;
		while (tmp_envlist->name[n])
			env_matrix[i][m++] = tmp_envlist->name[n++];
		env_matrix[i][m++] = '=';
		n = 0;
		while (tmp_envlist->value[n])
			env_matrix[i][m++] = tmp_envlist->value[n++];
		env_matrix[i][m] = '\0';
		i++;
		tmp_envlist = tmp_envlist->next;
	}
	env_matrix[i] = NULL;
	return (env_matrix);
}

