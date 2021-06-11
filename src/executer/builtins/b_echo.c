#include "minishell.h"

int	ft_carriage_return(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '-')
		return (EXIT_FAILURE);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	print_echo(t_tree *arg)
{
	char	**tableau;
	int		i;
	int		option;

	i = 0;
	tableau = arg->content;
	option = 0;
	while (tableau[i] && !ft_carriage_return(tableau[i]))
	{
		option = 1;
		i++;
	}
	while (tableau[i])
	{
		ft_putstr_fd(tableau[i], STDOUT_FILENO);
		if (tableau[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!option)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void	display_echo(t_tree *redir, t_tree *arg)
{
	redir = redir->branches->next->content;
	print_echo(arg);
}

int	b_echo(void *sh, t_tree *root)
{
	t_shell	*shell;
	t_tree	*tmp;

	shell = sh;
	(void)shell;
	if (root->branches)
	{
		tmp = root->branches->content;
		if (tmp->type == REDIRECT)
			ft_putchar_fd('\n', STDOUT_FILENO);
		else if (root->branches->next)
			display_echo(root, tmp);
		else
			print_echo(tmp);
	}
	else
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
