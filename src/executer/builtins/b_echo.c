#include "minishell.h"

void	print_echo(t_tree *arg, int fd)
{
	char	**tableau;
	int		i;

	i = 0;
	tableau = arg->content;
	while (tableau[i])
	{
		write(fd, tableau[i], ft_strlen(tableau[i]));
		i++;
	}
}

void	display_echo(t_tree *redir, t_tree *arg)
{
	int	fd;

	redir = redir->branches->next->content;
	fd = create_file_redirect(redir);
	print_echo(arg, fd);
}

int	b_echo(void *sh, t_tree *root)
{
	t_shell	*shell;
	t_tree	*tmp;
	int		fd;

	shell = sh;
	fd = 1;
	if (root->branches)
	{
		tmp = root->branches->content;
		if (tmp->type == REDIRECT)
			create_file_redirect(tmp);
		else if (root->branches->next)
			display_echo(root, tmp);
	}
	else
		write(fd, "\n", 1);
	return (0);
}
