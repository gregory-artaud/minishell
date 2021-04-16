#include "minishell.h"

int	exec_cmd(t_shell *sh)
{
	int	i;

	if (!sh || !sh->args || !sh->b_str)
		return (EXIT_FAILURE);
	i = -1;
	while (sh->b_str[++i])
		if (!ft_memcmp(sh->b_str[i], sh->args[0], sh->b_strlen[i]))
			return (sh->b_fct[i](sh));
	return (EXIT_SUCCESS);
}
