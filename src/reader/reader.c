#include "minishell.h"

void	read_line(t_shell *sh)
{
	int		c;

	set_terminal_settings();
	ft_bzero(sh->cmd_history->content, CMD_MAX_LENGTH);
	g_sh->current_line = g_sh->cmd_history;
	sh->i = 0;
	prompt();
	while (1)
	{
		c = ft_getchar();
		if (controller(c))
			break ;
		//printf("\ncurrent: %s\n", sh->cmd);
	}
	ft_putchar_fd('\n', 1);
	restore_terminal_settings();
}
