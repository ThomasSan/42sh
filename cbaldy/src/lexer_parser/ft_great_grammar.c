#include "lexer.h"


//creer des fonctions pour checker apres l'ampersand
int			ampersand_after_great(t_token *tok)
{
	// printf("cmd %s\n", tok->content);
	if (check_next_token(tok) == MINUS)
		return (1);
	else
		return (0);
}

int			rules_for_great(t_token *tok)
{
	// printf("cmd %s\n", tok->content);
	if (check_next_token(tok) == AMPERSAND)
	{
		if (tok->next)
			return (ampersand_after_great(tok->next));
		else
		{
			printf("return 0\n");
			return (0);
		}
	}
	if (check_next_token(tok) == WORDS)
	{
		printf("return 1\n");
		return (1);
	}
	printf("return 0\n");
	return (0);
}

int			rules_for_less(t_token *tok)
{
	// printf("cmd %s\n", tok->content);
	if (check_next_token(tok) == AMPERSAND)
	{
		if (tok->next)
			return (ampersand_after_great(tok->next));
		else
		{
			printf("return 0\n");
			return (0);
		}
	}
	if (check_next_token(tok) == WORDS)
	{
		printf("return 1\n");
		return (1);
	}
	printf("return 0\n");
	return (0);
}

// Acceptable apres less :
// WORDS (filename);
// Acceptable avant less :
// WORDS
// RIEN (premier arg)
// NUMBER (FD)

// Acceptable apres great :
// WORDS (filename);
// NUMBER (FD);
// Acceptable avant great :
// WORDS (CMD);
// RIEN (creee le fichier pointe a droite vide)
// NUMBER (FD);
// AMPERSAND
