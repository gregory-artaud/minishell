#include "minishell.h"

void	read_cmd(t_shell *sh)
{
	int	c;
	int	i;

	ft_bzero(sh->cmd, CMD_MAX_LENGTH);
	i = 0;
	while (1)
	{
		c = ft_getchar();
		if (c == '\n')
			return ;
		sh->cmd[i++] = (char)c;
	}
}
