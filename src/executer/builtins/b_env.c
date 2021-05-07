#include "minishell.h"

int	b_env(void *sh)
{
	t_shell	*shell;
	int i;

	shell = sh;
	i = 0;
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
	return (0);
}
