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
	struct stat	path_stat;
	int			res;

	res = stat(f, &path_stat);
	if (res == -1)
		return (-1);
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
	printf("type: %d\n", type);
	printf("minishell: %s: ", f);
	if (type == -1)
		printf("No such file or directory\n");
	else if (S_ISDIR(type))
		printf("is a directory\n");
	exit(126);
}
