#include "minishell.h"

int	b_env(void *sh, t_tree *root)
{
	t_shell	*shell;
	int i;

	(void)root;
	shell = sh;
	i = 0;
	while (i < shell->size_env)
	{
		if (shell->env[i])
			printf("%s\n", shell->env[i]);
		i++;
	}
	return (0);
}
