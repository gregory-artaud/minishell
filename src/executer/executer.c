#include "minishell.h"

int	run_tree(t_shell *sh, t_tree *tr)
{
	t_tree	*tmp;
	int		res;

	res = 0;
	if (!tr || tr->type > 4)
		return (EXIT_SUCCESS);
	if (tr->type == EXECUTABLE)
		return (execute_command(tr));
	if (!ft_memcmp(tr->content, SEPARATOR_SEPARATOR_TOKEN, S_S_T_LEN + 1))
	{
		tmp = ft_tr_leftchild(tr);
		res = execute_command(tmp);
		tmp = ft_tr_next_sibling(tmp);
		if (tmp)
			res = run_tree(sh, tmp);
	}
	return (res);
}

int	executer(t_shell *sh)
{
	int	status;

	if (!sh->ast)
		return (EXIT_SUCCESS);
	status = run_tree(sh, sh->ast);
	return (status);
}
