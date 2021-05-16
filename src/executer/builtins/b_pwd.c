#include "minishell.h"

int	b_pwd(void *sh, t_tree *root)
{
	t_shell	*shell;
	t_tree	*tmp;
	int		fd;

	shell = sh;
	fd = 1;
	if (root->branches)
	{
		tmp = root->branches->content;
		if (tmp->type == REDIRECT || root->branches->next)
			fd = create_file_redirect(tmp);
	}
	ft_putendl_fd(shell->pwd_path, fd);
	return (0);
}
