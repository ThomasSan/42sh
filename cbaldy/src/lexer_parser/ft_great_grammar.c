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
// RIEN (premier arg)
// NUMBER (FD)

// Acceptable apres great :
// WORDS (filename);
// Acceptable avant great :
// RIEN (creee le fichier pointe a droite vide)
// NUMBER (FD);
// AMPERSAND

// Acceptable apres dless :
// WORD (QUOTES REMOVED)
// Acceptable avant dless :
// RIEN ?
// WORD (CMD)

// Acceptable apres dgreat :
// WORD (FILENAME);
// Acceptable avant dgreat :
// NUMBER (FD)

// Acceptable apres less_and :
// DASH (moins)
// NUMBER (FD)
// Acceptable avant less_and :
// NUMBER (FD)
// RIEN

// Acceptable apres great_and :
// NUMBER (FD)
// WORD (Filename)
// Acceptable avant great_and :
// RIEN
// NUMBER (FD)

// Acceptable apres and_great :
// NUMBER OBLIGER 
// MINUS OBLIGER
// Acceptable avant and_great :
//