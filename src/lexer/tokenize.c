#include "minishell.h"

int	tokenize_cmd(char s[CMD_MAX_LENGTH], t_shell *sh)
{
	(void)s;
	(void)sh;
	return (EXIT_SUCCESS);
}

int	tokenize(char s[CMD_MAX_LENGTH], t_shell *sh)
{
	int	error;

	error = 0;
	error = tokenize_cmd(s, sh);
	return (error);
}
