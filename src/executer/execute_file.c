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

char	*build_path(char *path, char *exe)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(path, "/");
	res = ft_strjoin(tmp, exe);
	free(tmp);
	return (res);
}

int	get_file_type(char *f)
{
	struct stat path_stat;

	stat(f, &path_stat);
	return (path_stat.st_mode);
}

void	execute_path(char *exe, char **argv)
{
	char	**path;
	char	*file;
	int		i;

	path = ft_split(ft_lstgetenv("PATH"), ':');
	if (!path)
		return ;
	i = 0;
	while (path[i])
	{
		file = build_path(path[i], exe);
		if (!file)
			return ;
		execve(file, argv, list_to_char(g_sh->env));
		free(file);
		i++;
	}
}

void	exit_not_a_file_error(int type, char *f)
{
	int	fd;

	fd = g_sh->old_stdout;
	if (fd != -1)
		dup2(fd, STDOUT_FILENO);
	printf("minishell: %s:", f);
	if (S_ISDIR(type))
		printf(" is a directory\n");
	exit(126);
}

void	child_process(t_tree *tr)
{
	char	**argv;
	char	*exec;
	int		type;

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
