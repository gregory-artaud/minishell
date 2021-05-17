#include "minishell.h"

void	exec_builtin(t_tree *tr, int i)
{
	g_sh->status = g_sh->b_fct[i](g_sh, tr);
	return ;
}

void	test(int i)
{
	(void)i;
	printf("segfault!\n");
	exit(1);
}

void	exec_file(t_tree *tr)
{
	int		pid;
	char	**args;
	char	*exec;

	args = NULL;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		signal(SIGSEGV, test);
		if (!ft_tr_isleaf(tr))
			args = (char **)ft_tr_leftchild(tr)->content;
		exec = (char *)tr->content;
		printf("execve:%d\n", execve(exec, args, NULL));
	}
	else
	{
		// parent
		//printf("parent! (pid:%d)\n", pid);
		waitpid(pid, &(g_sh->status), 0);
	}
	return ;
}

void	execute_command(t_tree *tr)
{
	int		i;
	char	*exec;

	if (tr->type != EXECUTABLE) // TO REMOVE !
		return ;
	exec = (char *)tr->content;
	i = 0;
	while (i < NO_BUILTINS && ft_memcmp(exec, g_sh->b_str[i], g_sh->b_strlen[i]))
		i++;
	if (i < NO_BUILTINS)
		exec_builtin(tr, i);
	else
		exec_file(tr);
	return ;
}

void	run_tree(t_shell *sh)
{
	t_tree	*tr;

	tr = sh->ast;
	execute_command(tr);
}

int	executer(t_shell *sh)
{

	if (!sh->ast)
		return (EXE_ERR_MISSING_AST);
	generate_dot(sh->ast);
	run_tree(sh);
	return (EXIT_SUCCESS);
}
