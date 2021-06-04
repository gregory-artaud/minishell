#include "minishell.h"

void	child_process(t_tree *tr)
{
	char	**argv;
	char	*exec;
	int		type;

	if (g_sh->has_pipe)
		// redirect stdin to pipe
	argv = fill_argv(tr);
	exec = ft_strdup((char *)tr->content);
	set_signals();
	if (*exec != '/' && *exec != '.')
		execute_path(exec, argv);
	else
	{
		type = get_file_type(exec);
		if (!S_ISREG(type))
			exit_not_a_file_error(type, exec);
	}
	execve(exec, argv, list_to_char(g_sh->env));
	ft_free_strarray(argv);
	if (g_sh->old_stdout != -1)
		dup2(g_sh->old_stdout, STDOUT_FILENO);
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
