#include "minishell.h"

void	cp_pipe(int p1[2], int p2[2])
{
	p1[0] = dup(p2[0]);
	p1[1] = dup(p2[1]);
}

void	left_cmd(t_tree *tr)
{
	g_sh->has_pright = 1;
	close(g_sh->pright[0]);
	exit(execute_command(tr));
}

int	parent_process(int pid, t_tree *right)
{
	int	res;

	waitpid(pid, &res, 0);
	cp_pipe(g_sh->pleft, g_sh->pright);
	g_sh->has_pleft = 1;
	g_sh->has_pright = 0;
	close(g_sh->pright[0]);
	close(g_sh->pright[1]);
	close(g_sh->pleft[1]);
	return (run_tree(g_sh, right));
}

int	run_pipe(t_tree *tr)
{
	t_tree	*left;
	t_tree	*right;
	int		pid;
	int		error;

	left = ft_tr_leftchild(tr);
	right = ft_tr_next_sibling(left);
	error = pipe(g_sh->pright);
	if (error == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
		left_cmd(left);
	else if (pid > 0)
		return (parent_process(pid, right));
	return (-1);
}
