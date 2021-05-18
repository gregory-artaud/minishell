#include "minishell.h"

int	exec_builtin(t_tree *tr, int i)
{
	return (g_sh->b_fct[i](g_sh, tr));
}

char	**fill_argv(t_tree *tr)
{
	char	**argv;
	int		argc;
	int		len;
	t_tree	*node;
	int		i;

	node = ft_tr_leftchild(tr);
	if (!node || node->type != ARGUMENT)
		argc = 0;
	else
		argc = node->size;
	len = argc + 1;
	argv = malloc(sizeof(char *) * (len + 1));
	if (!argv)
		return (NULL);
	argv[0] = ft_strdup((char *)tr->content);
	argv[len] = NULL;
	i = -1;
	while (++i < argc)
		argv[i + 1] = ft_strdup(((char **)node->content)[i]);
	return (argv);
}

void	print_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		printf("%s\n", args[i++]);
}

int	exec_file(t_tree *tr)
{
	int		pid;
	int		status;
	char	**argv;
	char	*exec;

	pid = fork();
	if (pid == -1)
		printf("Internal error (cannot create new process)\n");
	else if (pid == 0)
	{
		argv = fill_argv(tr);
		exec = ft_strdup((char *)tr->content);
		//print_args(argv);
		free_shell(g_sh);
		execve(exec, argv, list_to_char(g_sh->env));
		ft_free_strarray(argv);
		printf("minishell: command not found: %s\n", exec);
		free(exec);
		exit(127);
	}
	else
	{
		g_sh->child_pid = pid;
		set_signals();
		waitpid(pid, &status, 0);
		reset_signals();
		return (WEXITSTATUS(status));
	}
	return (EXIT_FAILURE);
}

int	execute_command(t_tree *tr)
{
	int		i;
	char	*exec;

	if (tr->type != EXECUTABLE) // TO REMOVE !
		return (EXIT_FAILURE);
	exec = (char *)tr->content;
	i = 0;
	while (i < NO_BUILTINS && ft_memcmp(exec, g_sh->b_str[i], g_sh->b_strlen[i] + 1))
		i++;
	if (i < NO_BUILTINS)
		return (exec_builtin(tr, i));
	return (exec_file(tr));
}

int	run_tree(t_shell *sh)
{
	t_tree	*tr;

	tr = sh->ast;
	return (execute_command(tr));
}

int	executer(t_shell *sh)
{
	int	status;

	if (!sh->ast)
		return (EXE_ERR_MISSING_AST);
	//generate_dot(sh->ast);
	status = run_tree(sh);
	return (status);
}
