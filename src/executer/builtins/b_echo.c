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
		ft_putstr_fd(tableau[i], fd);
		if (tableau[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (!option)
		ft_putchar_fd('\n', fd);
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

	fd = -1;
	shell = sh;
	(void)shell;
	if (root->branches)
	{
		tmp = root->branches->content;
		if (tmp->type == REDIRECT)
		{
			fd = create_file_redirect(tmp);
			ft_putchar_fd('\n', fd);
		}
		else if (root->branches->next)
			display_echo(root, tmp);
		else
			print_echo(tmp, 1);
	}
	else
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
