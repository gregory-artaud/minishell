#include "minishell.h"

void	print_echo(t_tree *arg, int fd)
{
	char	**tableau;
	int		i;
	int		option;

	i = 0;
	tableau = arg->content;
	option = 0;
	if (!ft_strncmp("-n", tableau[i], 2))
	{
		option = 1;
		i++;
	}
	while (tableau[i])
	{
		write(fd, tableau[i], ft_strlen(tableau[i]));
		if (tableau[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (!option)
		write(fd, "\n", 1);
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
		{
			fd = create_file_redirect(tmp);
			write(fd, "\n", 1);
		}
		else if (root->branches->next)
			display_echo(root, tmp);
		else
			print_echo(tmp, 1);
	}
	else
		write(fd, "\n", 1);
	return (0);
}
