#include "../minishell.h"

void print_matrix_of_char(char **matrix)
{
	int i;

	i = 0;
	while (matrix[i])
	{
		printf("%s\n", matrix[i]);
		i++;
	}
}

void print_matrix_of_int(int **matrix, int limit_row,int limit_column)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (i < limit_row)
	{
		j = 0;
		while(j < limit_column)
		{
			printf("[%d]", matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
