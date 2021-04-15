#include "minishell.h"

void	read_cmd(t_shell *sh)
{
	int	c;
	int	i;

	ft_bzero(sh->cmd, CMD_MAX_LENGTH);
	c = ft_getchar();
	i = 0;
	while (c != '\n')
	{
		sh->cmd[i++] = (char)c;
		c = ft_getchar();
	}
}
