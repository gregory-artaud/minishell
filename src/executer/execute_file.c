#include "minishell.h"

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

void	child_process(t_tree *tr)
{
	char	**argv;
	char	*exec;

	argv = fill_argv(tr);
	exec = ft_strdup((char *)tr->content);
	free_shell(g_sh);
	set_signals();
	execve(exec, argv, list_to_char(g_sh->env));
	ft_free_strarray(argv);
	printf("minishell: command not found: %s\n", exec);
	free(exec);
	exit(127);
}

int	exec_file(t_tree *tr)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid == 0)
		child_process(tr);
	else if (pid > 0)
	{
		g_sh->child_pid = pid;
		set_signals();
		waitpid(pid, &status, 0);
		reset_signals();
		return (WEXITSTATUS(status));
	}
	return (EXE_ERR_FORK);
}
