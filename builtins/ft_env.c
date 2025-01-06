#include "../minishell.h"

int	ft_env(t_env *lenvlist)
{
	t_env	*tmp_envlist;

	if (!lenvlist)
		return (0);
	tmp_envlist = lenvlist;
	while (tmp_envlist)
	{
		printf("%s=%s\n",tmp_envlist->name, tmp_envlist->value);
		tmp_envlist = tmp_envlist->next;
	}
	return (1);
}

t_env	*copy_envp(char **envp)
{
	t_env	*envlist;
	t_env	*envnode;
	int		i;

	envlist = NULL;
	i = 0;
	while (envp[i])
	{
		envnode = create_lenvnode(envp[i]);
		if (!envnode)
		{
			ft_freelist(envlist);
			return (NULL);
		}
		envlist_append(envnode, &envlist);
		i++;
	}
	return (envlist);
}
