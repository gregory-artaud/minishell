#include "minishell.h"

/*
** TO-DO HERE:
**		- command historic with arrow keys up/down
**		- handling CTRL-D, CTRL-C and CTRL-\
*/
void	read_line(t_shell *sh)
{
	int	c;
	int	i;

	ft_bzero(sh->cmd, CMD_MAX_LENGTH);
	i = 0;
	while (1)
	{
		c = ft_getchar();
		if (c == '\n')
			break ;
		sh->cmd[i++] = (char)c;
	}
}

void	lexer(t_shell *sh)
{
	char	tmp[CMD_MAX_LENGTH];
	int		i;
	int		j;

	read_line(sh);
	ft_bzero(tmp, CMD_MAX_LENGTH);
	i = 0;
	j = 0;
	while (sh->cmd[i])
		process_line(tmp, sh, &i, &j);
	printf("%s\n", tmp);
}
