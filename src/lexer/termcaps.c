#include "minishell.h"

/*
** TO-DO HERE:
**		- command historic with arrow keys up/down
*/
void	termcap(char c, char *tmp, int *i)
{
	if (c == 'A')
		term_up(c, tmp, i);
	else if (c == 'B')
		term_down(c, tmp, i);
	else if (c == 'C')
		term_right(c, tmp, i);
	else if (c == 'D')
		term_left(c, tmp, i);
}

int	controller(char c, char *tmp, int *i)
{
	if (c == '\n')
		return (1);
	else if (c == EOF)
	{
		if (!(*i))
		{
			ft_bzero(tmp, CMD_MAX_LENGTH);
			ft_strlcpy(tmp, "exit", 5);
			return (1);
		}
	}
	else if (c == '\033')
	{
		(void)ft_getchar();
		c = ft_getchar();
		termcap(c, tmp, i);
	}
	if (c > 0)
		tmp[(*i)++] = (char)c;
	return (0);
}