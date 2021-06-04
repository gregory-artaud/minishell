#include "minishell.h"

int	process_backslash(char s[CMD_MAX_LENGTH], int *i, char *wd, int *j)
{
	(void)wd;
	(void)j;
	(*i)++;
	if (!s[*i])
		return (LEX_ERR_EOL_AFTER_ESCAPE);
	wd[(*j)++] = s[(*i)++];
	return (EXIT_SUCCESS);
}

int	process_double_quote(char s[CMD_MAX_LENGTH], int *i, char *wd, int *j)
{
	int	error;

	(*i)++;
	while (s[*i] && s[*i] != DOUBLE_QUOTE)
	{
		if (s[*i] == BACKSLASH && is_special(s[*i + 1]))
		{
			error = process_backslash(s, i, wd, j);
			if (error)
				return (error);
		}
		else if (s[*i] == ENV_VARIABLE_PREFIX)
		{
			error = process_env(s, i, wd, j);
			if (error)
				return (error);
		}
		else
			wd[(*j)++] = s[(*i)++];
	}
	if (s[*i] != DOUBLE_QUOTE)
		return (LEX_ERR_OPEN_DOUBLE_QUOTE);
	(*i)++;
	return (EXIT_SUCCESS);
}

int	process_single_quote(char s[CMD_MAX_LENGTH], int *i, char *wd, int *j)
{
	(*i)++;
	while (s[*i] && s[*i] != SINGLE_QUOTE)
		wd[(*j)++] = s[(*i)++];
	if (s[*i] != SINGLE_QUOTE)
		return (LEX_ERR_OPEN_SINGLE_QUOTE);
	(*i)++;
	return (EXIT_SUCCESS);
}
