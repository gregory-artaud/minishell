#include "minishell.h"

int	b_exit(void *sh, t_tree *root)
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
	if (fd > 0)
	{
		clear_ast(&shell->ast);
		printf("exit\n");
		exit(0);
	}
	return (0);
}
