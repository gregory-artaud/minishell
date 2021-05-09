#include "minishell.h"

void	read_line(t_shell *sh)
{
	int		c;

	set_terminal_settings();
	ft_bzero(sh->cmd, CMD_MAX_LENGTH);
	sh->i = 0;
	while (1)
	{
		c = ft_getchar();
		if (controller(c))
			break ;
		//printf("\ncurrent: %s\n", sh->cmd);
	}
	restore_terminal_settings();
}
