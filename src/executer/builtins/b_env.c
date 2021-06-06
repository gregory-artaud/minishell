#include "minishell.h"

int	find_sep(char *str, char sep)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == sep)
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

void	print_env(t_list *env)
{
	while (env)
	{
		if (!find_sep(env->content, '='))
			ft_putendl_fd(env->content, STDOUT_FILENO);
		env = env->next;
	}
}

void	display_env(t_list *env, int display)
{
	if (display)
		print_env(env);
}

int	b_env(void *sh, t_tree *root)
{
	t_shell	*shell;

	(void)root;
	shell = sh;
	print_env(shell->env);
	return (0);
}
