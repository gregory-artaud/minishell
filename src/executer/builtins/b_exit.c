#include "minishell.h"

int		verif_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (EXIT_FAILURE);
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	verif_arg(t_tree *arg, t_shell *shell)
{
	char	**tableau;
	int		nb;

	tableau = arg->content;
	if (verif_num(tableau[0]))
	{
		printf("minishell: exit: %s: numeric argument required\n", tableau[0]);
		nb = 255;
	}
	else if (arg->size > 1)
	{
		printf("minishell: exit: too many arguments\n");
		return (EXIT_FAILURE);
	}
	else
		nb = ft_atoi(tableau[0]);
	free_shell(shell);
	exit(nb);
	return (EXIT_SUCCESS);
}

void	exit_shell(t_shell *shell)
{
	free_shell(shell);
	exit(shell->status);
}

int	b_exit(void *sh, t_tree *root)
{
	t_shell	*shell;
	t_tree	*tmp;

	shell = sh;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (root->branches)
	{
		tmp = root->branches->content;
		if (tmp->type == ARGUMENT)
			return (verif_arg(tmp, shell));
		else
			exit_shell(shell);
	}
	else
		exit_shell(shell);
	return (EXIT_SUCCESS);
}
