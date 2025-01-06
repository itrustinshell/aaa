#include "../minishell.h"

/*
TODO: 'rrr'rrrr deve essere riconosciuto come un unico token...
 */
char **matrixalloc(int n_tokens)
{
	char **matrix_to_ret;

	matrix_to_ret = NULL;
	matrix_to_ret = (char **)malloc((n_tokens + 1) * sizeof(char *));
	if (!matrix_to_ret)
		return (NULL);
	return (matrix_to_ret);
}

char *tokenalloc(char *inputstr, int index, int len)
{
	char *token;
	int t;

	token = (char *)malloc((len + 1) * sizeof(char));
	if (token == NULL)
		return (NULL);
	t = 0;
	while (t < len)
	{
		token[t] = inputstr[index + t];
		t++;
	}
	token[t] = '\0';
	//printf("token_len: %d\n",t);
	return (token);
}

void free_matrix(char **tokenmatrix)
{
	int t;

	t = 0;
	while (tokenmatrix[t])
	{
		free(tokenmatrix[t]);
			t++;
	}
	free(tokenmatrix);
}

char *create_token_wordled(char *inputstr, int *iterator)
{
		int i;
		int len;
		char *token;

		token = NULL;
		i = *iterator;
		len = 0;
		while (
			inputstr[i + len] &&
			!ft_isspace(inputstr[i + len]) &&
			!ft_issymbol(inputstr[i + len])
		)
			len++;
		if (len > 0)
		{
			token = tokenalloc(inputstr, i, len);
			if (token == NULL)
				return (NULL);
			i = i + len;
		}
		*iterator = i;
		return (token);
}

char *create_token_symbolled(char *inputstr, int *iterator)
{
	char *token;
	int i;
	int len;
	int starting_index;
	int is_symbol;

	token = NULL;
	i = *iterator;
	starting_index = i;
	is_symbol = check_symbols(inputstr, &i);
	if (is_symbol)
	{	
		
		len = i - starting_index + 1;//nota 33
		if (inputstr[i] == DOUBLE_QUOTE)
		{
			starting_index += 1;
			len = i - starting_index;
		}
		token = tokenalloc(inputstr, starting_index, len);
	}
	*iterator = i;
	return (token);
}


/*given a string, it calculates how many words it is composed of*/
char **create_tokenmatrix(char *inputstr, int n_tokens)
{
	char **tokenmatrix;
	int i;
	int t;

	tokenmatrix = matrixalloc(n_tokens);
	if (!tokenmatrix)
		return (NULL);
	t = 0;
	i = 0;
	while (t < n_tokens)
	{
		while (ft_isspace(inputstr[i]))
			i++;
		if (inputstr[i] && !ft_issymbol(inputstr[i]))
			tokenmatrix[t++] = create_token_wordled(inputstr, &i);
		if (ft_issymbol(inputstr[i]))
			tokenmatrix[t++] = create_token_symbolled(inputstr, &i);
		i++; //si finisce sempre sul carattere che precede un token ...
	}
	tokenmatrix[t] = NULL;
	return tokenmatrix;
}

// nota 33 la i potenzialmente è andata avanti in chec_symbol. La sua precedente posizione è salvata in tmp prima di eseguire check_symbol. se la i non è andata avanti il risultato di questa len sarà quello che deve eessere ovvero 0. Significa che non vi erano simboli
	
/*XXX sappiamo che in checksymbol avviene anche il check su double single e altri element
 i...
 nel caso di double e single il chek consiste nell'iterazione al successivo single o 
 double per accertare la chiusura delle quotes. 
 Pertanto il cursore si fermerebbe sull'ultimo apice...ecop perchè la len qui 
 deve essere aggiunta...perchè io devo includere anche quell'apice e poi inserire un \0..
 .questo ai fini del token.Per intenderci quando hai il $ciao l'iterazione 
 non si ferma sulla o ma su un eventuale spazio  e un eventuaesegno...
 questi utlimi non li vogliao mettere nel token che terminerà appunto con la o di ciao e il nullterminator predisposto dalla funzione create_token. Nell'altro caso, con le quotes,,il termine è appunto un altra quotes " (che se ci pensi sarebbe un simbolo...proprio come il dollar sign finiva o con uno spazio o cono un siimbolo...in questo caso termina con il simbolo i quotes...., ma questa volta noi vogliamo inserire questa nel token...pertanto in questa funzione daremo una len aumentata di uno da passare a create token che partendo dallo strting point che gli abbiamo dato, si posiazione sullo starting nella stringa e itera per quella len...aggiungendo poi a sua volta il suo spazio per \0.
*/	

	/*nota 44 anche in tal caso io so che se c'è un < possono accadere due casi: o che è singolo o che è doppio. Nel primo caso avrò una len di zero...e non mi basta perchè poi in create_tken io aggiungo solo una posizione...in questa funzione infatti ogni volta che la len è zero e contiene un valore che devo restituire allora devo già qui aumentarla di uno...ovvero di quella posizione da riservare appunto al char che voglio restituire come token. Nell'altro caso di cui sopra avremo due consecutivi <<. in tal caso io so che avrò avuto una iterazione prima in checksymbol che avrà mandato la i proprio sullìultimo <...ma come nel caso dele virgolette io questo ultimo voglio inserirlo nel token...quindi aumenterò di uno la len anche in tal caso.*/


 //nota 88 qui sostanzilamente sono nella condizione piu generale in qui ho un simbolo. Quinsdi entrando qui io so che ho un simbolo. Ora se ho len zero devo sempre aumentarla di uno per riservare appunto spazioe a quel simbolo da mandare in stampa.

 //nota 66 l'eventuale starting point da cui copiare il token è appunto i - la lunghezza appena trovata. Se la lunghezza è 0 sarà allora la i stessa (in tal caso la i non sarà andata avanti)
	
