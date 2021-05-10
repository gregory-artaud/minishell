#include "minishell.h"

int	ctrl_d(void)
{
	ft_putstr_fd("^D", 1);
	if (g_sh->i == 0)
	{
		ft_strlcpy(g_sh->cmd_history->content, "exit", 5);
		return (1);
	}
	return (0);
}

int	ctrl_c(void)
{
	ft_bzero(g_sh->cmd_history->content, CMD_MAX_LENGTH);
	g_sh->current_line = g_sh->cmd_history;
	g_sh->i = 0;
	ft_putstr_fd("^C\n", 1);
	prompt();
	return (0);
}

void	new_cmd(int i)
{
	(void)i;
	ctrl_c();
	return ;
}
