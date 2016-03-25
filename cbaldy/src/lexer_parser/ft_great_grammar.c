#include "lexer.h"

int			rules_for_great(t_token *tok)
{
	if (check_next_token(tok) == WORDS)
	{
		tok->next->type = FILENAME;
		return (1);
	}
	return (0);
}

int			rules_for_less(t_token *tok)
{
	if (check_next_token(tok) == WORDS)
	{
		tok->next->type = FILENAME;
		return (1);
	}
	return (0);
}

int			rules_for_great_and(t_token *tok)
{
	if (check_next_token(tok) == WORDS ||check_next_token(tok) == MINUS
		|| check_next_token(tok) == NUMBERS)
		return (1);
	return (0);
}

int			rules_for_less_and(t_token *tok)
{
	if (check_next_token(tok) == MINUS || check_next_token(tok) == NUMBERS)
		return (1);
	return (0);
}

int			rules_for_and_great(t_token *tok)
{
	if (check_next_token(tok) == WORDS)
		return (1);
	return (0);
}

// Acceptable apres great :
// WORDS (filename);
// Acceptable avant great :
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
// DASH (moins)
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