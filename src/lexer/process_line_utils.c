#include "minishell.h"

int	no_env_var_name(char tmp[CMD_MAX_LENGTH], int *j)
{
	tmp[(*j)++] = ENV_VARIABLE_PREFIX;
	return (EXIT_SUCCESS);
}

int	is_special(char c)
{
	return (c == BACKSLASH || c == DOUBLE_QUOTE
		|| c == ENV_VARIABLE_PREFIX);
}
