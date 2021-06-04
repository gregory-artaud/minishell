#include "minishell.h"

int	run_semi_column(t_tree *tr)
{
	t_tree *tmp;
	int		res;

	tmp = ft_tr_leftchild(tr);
	res = execute_command(tmp);
	tmp = ft_tr_next_sibling(tmp);
	if (tmp)
		res = run_tree(g_sh, tmp);
	return (res);
}

int	run_pipe(t_tree *tr)
{
	t_tree	*cmd1;
	t_tree	*cmd2;
	int		res;
	int		error;

	error = pipe(g_sh->pfd);
	if (error == -1)
		return (-1);
	g_sh->has_pipe = 1;
	cmd1 = ft_tr_leftchild(tr);
	cmd2 = ft_tr_next_sibling(cmd1);
	if (!cmd2)
		return (-1);
	res = execute_command(cmd1);
	res = run_tree(g_sh, cmd2);
	return (res);
}

int	run_tree(t_shell *sh, t_tree *tr)
{
	int		res;

	res = 0;
	if (!tr || tr->type > 4)
		return (EXIT_SUCCESS);
	if (tr->type == EXECUTABLE)
		return (execute_command(tr));
	if (!ft_memcmp(tr->content, SEPARATOR_PIPE_TOKEN, S_P_T_LEN + 1))
	{
		if (do_pipe())
			res = run_pipe(tr);
		else
			((char *)tr->content)[0] = ';';
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
	status = run_tree(sh, sh->ast);
	return (status);
}
