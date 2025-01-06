	char **l_envp;
	char test_g_envp[3][8] = {"aaa=123", "bbb=123", "ccc=123"};
	char test_l_envp[3][8] = {"sss=123", "ttt=123", "rrr=123"};

	l_envp = NULL;
	g_envp = test_create_envp(test_g_envp);
	l_envp = test_create_envp(test_l_envp);

	print_matrix_of_char(g_envp);
	print_matrix_of_char(l_envp);




char **convert_list_to_matrix(t_env *envlist)
{
	int lenlist;
	t_env *tmp_envlist;
	char **env_matrix;
	int len_name;
	int len_value;
	int i;
	int n;
	int m;

	tmp_envlist = envlist;
	printf("inizio a convertire\n");
	lenlist = envlist_len(tmp_envlist);
	printf("la lista si compone di: %d nodi.\n", lenlist);

	env_matrix = (char **)malloc((lenlist + 1) * sizeof(char *));

	i = 0;
	while (tmp_envlist)
	{

		//calcola la lungezza di name
		len_name = ft_strlen(tmp_envlist->name);
		len_value = ft_strlen(tmp_envlist->value);
		env_matrix[i] = (char *)malloc((len_name + len_value + 1 + 1) * sizeof(char));
		n = 0;
		m = 0;
		while(tmp_envlist->name[n])
		{
			env_matrix[i][m] = tmp_envlist->name[n];
			m++;
			n++;
		}
		env_matrix[i][m] = '=';
		m++;
		n = 0;
		while(tmp_envlist->value[n])
		{
			env_matrix[i][m] = tmp_envlist->value[n];
			m++;
			n++;
		}
		env_matrix[i][m] = '\0';
		i++;
		tmp_envlist = tmp_envlist->next;
	}
	env_matrix[i] = NULL;
	return (env_matrix);
}

t_env *nodedup(t_env *node)
{
	t_env *duplicated_node;

	if(!node)
		return (NULL);
	duplicated_node = (t_env *)malloc(sizeof(t_env));
	init_envnode(duplicated_node);
	duplicated_node->name = strdup(node->name);
	duplicated_node->value = strdup(node->value);
	printf("ecco il nodo duplicato:%s=%s\n",duplicated_node->name, duplicated_node->value);
	return (duplicated_node);
}


int builtinex(t_cmd *cmd, t_env **env)
{
	int ret;

	ret = 1;
	if (strcmp(cmd->cmd, "env") == 0)
		printenvlist(*env);
	else if (strcmp(cmd->cmd, "export") == 0)
	{
		if (exportcheck(cmd->args) == 1)
			ft_export(cmd->args[1], env);
	}
	else if (strcmp(cmd->cmd, "exit") == 0)
	{
		//ft_freematrix(matrix);
		//free(inputstr);
		// (void)inputstr;
		// inputstr = NULL;
		exit(1);
	}
	else
		ret = 0;
	return (ret);
}

// int check_redirection_symbol(char **tokenmatrix) //cerca se c'è almeno una redirection
// {
// 	int	i;

// 	i = 0;
// 	while (tokenmatrix[i])
// 	{
// 		if (tokenmatrix[i][0] != OUTPUT_REDIRECTION)
// 			i++;
// 		else
// 		{
// 			return (THERE_IS_A_REDIRECTION);
// 		}
// 	}
// 	return (THERE_IS_NOT_A_REDIRECTION);
// }


/*check if it is at least one pipe*/
int pipecheck(char **tokenmatrix) 
{
	int	i;

	i = 0;
	while (tokenmatrix[i])
	{
		if (tokenmatrix[i][0] != PIPE)
			i++;
		else
			return (THERE_IS_A_PIPE);
	}
	return (THERE_IS_NOT_A_PIPE);
}
