#include "minishell.h"

int	ctrl_d(void)
{
	if (g_sh->i == 0)
	{
		ft_strlcpy(g_sh->cmd, "exit", 5);
		return (1);
	}
	return (0);
}

int	ctrl_c(void)
{
	ft_bzero(g_sh->cmd, CMD_MAX_LENGTH);
	g_sh->i = 0;
	write(1, "\n", 1);
	prompt();
	return (0);
}

void	new_cmd(int i)
{
	(void)i;
	ctrl_c();
	return ;
}
