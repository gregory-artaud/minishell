#include "minishell.h"

int	del(void)
{
	int		i;
	char	*s;

	if (g_sh->i <= 0)
		return (0);
	s = (char *)g_sh->current_line->content;
	(g_sh->i)--;
	i = g_sh->i;
	while (s[i])
	{
		s[i] = s[i + 1];
		i++;
	}
	return (0);
}
