#include "minishell.h"

int	b_env(void *sh, t_tree *root)
{
	t_shell	*shell;
	t_list	*tmp;

	(void)root;
	shell = sh;
	tmp = shell->env;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
	return (0);
}