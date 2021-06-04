#include "minishell.h"

int	run_semi_column(t_tree *tr)
{
	t_tree	*tmp;
	int		res;

	tmp = ft_tr_leftchild(tr);
	res = execute_command(tmp);
	tmp = ft_tr_next_sibling(tmp);
	if (tmp)
		res = run_tree(g_sh, tmp);
	return (res);
}

int	run_tree(t_shell *sh, t_tree *tr)
{
	int		res;
	int		flag;

	(void)sh;
	flag = 0;
	res = 0;
	if (!tr || tr->type > 4)
		return (EXIT_SUCCESS);
	if (tr->type == EXECUTABLE)
		return (execute_command(tr));
	if (!ft_memcmp(tr->content, SEPARATOR_PIPE_TOKEN, S_P_T_LEN + 1))
	{
		flag = do_pipe(tr);
		if (flag == 1)
			res = run_pipe(tr);
		else if (flag == 0)
			((char *)tr->content)[0] = ';';
		else
			res = 258;
	}
	if (!ft_memcmp(tr->content, SEPARATOR_SEPARATOR_TOKEN, S_S_T_LEN + 1))
		res = run_semi_column(tr);
	return (res);
}

int	executer(t_shell *sh)
{
	int	status;

	if (!sh->ast)
		return (EXIT_SUCCESS);
	generate_dot(sh->ast);
	status = run_tree(sh, sh->ast);
	return (status);
}
