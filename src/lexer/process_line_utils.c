#include "minishell.h"

void	no_env_var_name(char tmp[CMD_MAX_LENGTH], int *j)
{
	tmp[(*j)++] = ENV_VARIABLE_TOKEN;
	return ;
}
