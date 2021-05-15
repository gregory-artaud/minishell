#include "minishell.h"

void	print_env(t_list *env, int fd)
{
	while (env)
	{
		write(fd, env->content, ft_strlen(env->content));
		write(fd, "\n", 1);
		env = env->next;
	}
}

void	display_env(t_tree *root, t_list *env, int display)
{
	int	fd;

	fd = create_file_redirect(root);
	if (display)
		print_env(env, fd);
}

int	b_env(void *sh, t_tree *root)
{
	t_shell	*shell;
	t_list	*env;
	t_tree	*tmp;

	shell = sh;
	env = shell->env;
	if (root->branches)
  {
		tmp = root->branches->content;
		if (tmp->type == REDIRECT)
			display_env(tmp, shell->env, 1);
		else if (root->branches->next)
			display_env(tmp, shell->env, 0);
	}
	else
		print_env(shell->env, 1);
	return (0);
}
