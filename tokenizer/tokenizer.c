
#include "../minishell.h"

/*
Memory: no_memory_allocation
*/
char **tokenizer(char *str_to_tokenize)
{
	char **tokens_matrix;
	int n_tokens;

	if (!str_to_tokenize)
		return (NULL);
	tokens_matrix = NULL;
	n_tokens = get_num_of_tokens(str_to_tokenize);
	if (n_tokens < 0)
		return (NULL);
	tokens_matrix = create_tokenmatrix(str_to_tokenize, n_tokens);
	if (tokens_matrix == NULL)
		return (NULL);
	return (tokens_matrix);
}

