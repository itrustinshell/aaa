#include "../minishell.h"

int	ends_with_equal_sign(char *str)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (str[i])
		i++;
	i--;
	if (str[i] == '=')
		ret = 1;
	return (ret);
}

int	there_is_equal_before_end(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	exportcheck(char **matrix)
{
	if (matrixlen(matrix) > 3)
	{
		printf("ci sono piu di 3 pezzi con l'export\n");
		return (0);
	}
	if (!matrix[1])
	{
		printf("non c'è il pezzo con l'uguale\n");
		return (0);
	}
	if (!ends_with_equal_sign(matrix[1]))
	{
		if (!there_is_equal_before_end(matrix[1]))
			return (0);
		else if (matrixlen(matrix) >= 3)
		{
			printf("troppi argomenti\n");
			return (0);
		}
		else
		{
			printf("ok qui puoi lavorare per estrarre la variabile\n");
			return (1);
		}
	}
	else
	{
		if (matrixlen(matrix) > 3)
		{
			printf("AAA: il simbolo di uguale c'è ma ci sono troppi argomenti\n");
			return (0);
		}
		else
		{
			printf("si la prima parte termina con il simbolo uguale\n");
			return (2);
		}
	}
	return 0;
}

void addto_globalenv(t_env **local_envlist, char *str)
{
	t_env *local_envnode;

	local_envnode = create_lenvnode(str);
	if (local_envnode)
		printf("il nodo esiste. Il name è %s, mentre il valore è %s\n", local_envnode->name, local_envnode->value);
	envlist_append(local_envnode, local_envlist);
	if (local_envlist)
		printf("finalmente la lista estiste\n");
	else
		printf("attenzione ho aggiunto un nodo ma c'è qualcosa che non va: la lista non esista\n");	
}

t_env *access_envar(char *namevar, t_env *list) //verifica se esiste la variabile
{
	t_env	*tmp_list;

	if (!list)
	{
		printf("non esiste ancora alcuna variabile globlae\n");
		return (NULL);
	}
	if (!namevar)
	{
		printf("non hai indicato quale variabile vuoi controllare\n");
		return (NULL);
	}
	tmp_list = list;
	while (tmp_list)
	{
		if (strcmp(tmp_list->name, namevar) == 0)
		{
			printf("SI! La variabile ESISTE\n");
			return (tmp_list);
		}
		tmp_list = tmp_list->next;
	}
	printf("Attenzione: la variabile NON esiste!\n");
	return (NULL);
}

void	ft_export(char *namevar, t_env **global_envlist)
{
	t_env	*found_global_envar;
	t_env	*new_node;

	new_node = create_lenvnode(namevar);
	if (new_node)
		printf("il nodo esiste. Il name è %s, mentre il valore è %s\n", new_node->name, new_node->value);
	found_global_envar = access_envar(new_node->value, *global_envlist);
	if (found_global_envar)
	{
		printf("la variabile già esiste nell'ambiente globale!");
		return ;
	}
	else
		envlist_append(new_node, global_envlist);
}
