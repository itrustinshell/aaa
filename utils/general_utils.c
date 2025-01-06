#include "../minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	matrixlen(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

int	ft_isspace(char char_to_check)
{
	if (char_to_check == SPACE)
		return (IS_SPACE);
	else if (char_to_check == TABULATION)
		return (IS_SPACE);
	else if (char_to_check == NEW_LINE)
		return (IS_SPACE);
	return (IS_NOT_SPACE);
}

char	*strjoin(char *str, char *str_toadd)
{
	int		lenstr;
	int		len_strtoadd;
	char	*str_toret;
	int		i;
	int		j;

	lenstr = ft_strlen(str);
	len_strtoadd = ft_strlen(str_toadd);
	str_toret = (char *)malloc((lenstr + len_strtoadd + 1) * sizeof(char));
	i = 0;
	while (str[i])
	{
		str_toret[i] = str[i];
		i++;
	}
	j = 0;
	while (str_toadd[j])
	{
		str_toret[i + j] = str_toadd[j];
		j++;
	}
	return (str_toret);
}
