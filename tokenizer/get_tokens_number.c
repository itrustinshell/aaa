#include "../minishell.h"
// get_tokens_number
/*
AAA quando dopo < metto solo una lettera ad es <d
non riconosce la d come token separato da <

 */

/*given a char it checks if it is a given symbol
Memory: no_memory_allocation
*/
int	ft_issymbol(char char_to_check)
{
	if (char_to_check == INPUT_REDIRECTION)
		return (IS_SYMBOL);
	else if(char_to_check == OUTPUT_REDIRECTION)
		return (IS_SYMBOL);
	else if (char_to_check == PIPE)
		return (IS_SYMBOL);
	else if (char_to_check == DOLLAR_SIGN)
		return (IS_SYMBOL);
	else if (char_to_check == SINGLE_QUOTE)
		return (IS_SYMBOL);
	else if (char_to_check == DOUBLE_QUOTE)
		return (IS_SYMBOL);
	return (IS_NOT_SYMBOL);
}

/*
Memory: no_memory_allocation
*/
int singlequote_iteration(char *inputstr, int *iterator, char symbol)
{
	int i;

	i = *iterator;
	i++; //mi sposo a destra dell'apice di apertura
	while (inputstr[i] && inputstr[i] != symbol)
		i++; //quando esce dovrebbe essere sull'apice di chiusura a meno che non esista
	if (inputstr[i] != symbol) //quando le virgolette non si chiudono
	{
		write(1,"Error message: unclosed quotes.\n", 32);
		return (-1);
	}
	*iterator = i;
	return (1);
}

/*
Memory: no_memory_allocation
*/
int doublequote_iteration(char *inputstr, int *iterator, char symbol)
{
	int i;

	i = *iterator;
	i++; //mi sposo a destra dell'apice di apertura
	while (inputstr[i] && inputstr[i] != symbol)
		i++; //quando esce dovrebbe essere sull'apice di chiusura a meno che non esista
	if (inputstr[i] != symbol) //quando le virgolette non si chiudono
	{
		write(1,"Error message: unclosed quotes.\n", 32);
		return (-1);
	}
	*iterator = i;
	return (1);
}

/*
Memory: no_memory_allocation
*/
int dollarsign_iteration(char *inputstr, int *iterator, char symbol)
{
	int i;

	i = *iterator;
	if (inputstr[i] == symbol && !ft_isspace(inputstr[i + 1]))
	{
		i++; //mi sposto a destra del simbolo di dollaro (aaa stiamo parlanod di variabili)
		while (inputstr[i] && !ft_isspace(inputstr[i]) && !ft_issymbol(inputstr[i]))
			i++;
		if (ft_issymbol(inputstr[i]))
			i--; //quando esce dal while si trova su un simbolo o su uno spazio
	}
	*iterator = i;
	return i;
}

/*
Memory: no_memory_allocation
*/
int symbol_iteration(char *inputstr, int *iterator, char symbol)
{
	int i;
	
	i = *iterator;
	if (symbol == SINGLE_QUOTE)
	{
		if (singlequote_iteration(inputstr, &i, symbol) < 0)
			return (-1);
	}
	else if (symbol == DOUBLE_QUOTE)
	{
		if (doublequote_iteration(inputstr, &i, symbol) < 0)
			return (-1);
	}
	else if (symbol == DOLLAR_SIGN)
		dollarsign_iteration(inputstr, &i, symbol);
	*iterator = i;
	return (1);
}


/*trova un simbolo e aggiorna l'indice lungo la stringa da tokenizzare 
ritornando il numero di tokens
Memory: no_memory_allocation
*/
int	check_symbols(char *inputstr, int *iterator)
{
	int n_tokens;
	int i;

	i = *iterator;
	n_tokens = 0;
	if (ft_issymbol(inputstr[i]))
	{
		n_tokens += 1;
		if (inputstr[i] == SINGLE_QUOTE)
		{
			if(symbol_iteration(inputstr, &i, SINGLE_QUOTE) < 0)
				return (-1);
		}
		else if (inputstr[i] == DOUBLE_QUOTE)
		{
			if (symbol_iteration(inputstr, &i, DOUBLE_QUOTE) < 0)//AAA manage solo quando c'è il dollar sign
				return (-1);
		}
		else if (inputstr[i] == DOLLAR_SIGN)
			symbol_iteration(inputstr, &i, DOLLAR_SIGN);
		else if (inputstr[i] == INPUT_REDIRECTION && inputstr[i + 1] == INPUT_REDIRECTION)
			i += 1;
		else if (inputstr[i] == OUTPUT_REDIRECTION && inputstr[i + 1] == OUTPUT_REDIRECTION)
			i += 1;
		//else
		//	i++;
	}
	*iterator = i;
	return (n_tokens);
}

/*
given a string, it calculates how many words it is composed of
Memory: no_memory_allocation
*/
int get_num_of_tokens(char *str_to_tokenize)
{
	int n_tokens;
	int padlock;
	int i;
	int is_symbol;

	n_tokens = 0;
	i = -1;
	while (str_to_tokenize[++i])
	{
		while (ft_isspace(str_to_tokenize[i]))
			i++;
		padlock = UNLOCKED;
		while (str_to_tokenize[i] && !ft_isspace(str_to_tokenize[i]) && !ft_issymbol(str_to_tokenize[i]))
		{
			if (padlock == UNLOCKED)
			{
				n_tokens += 1;
				padlock = LOCKED;
			}
			i++;
		}
		if ((is_symbol = check_symbols(str_to_tokenize, &i)) >= 0)
			n_tokens += is_symbol;
		else if (is_symbol < 0)
			return (-55);				
	}
	return (n_tokens);
}

