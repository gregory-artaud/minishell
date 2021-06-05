#include "minishell.h"

int	change_dir(t_tree *root)
{
	char	**path;
	char	cwd[PWD_PATH_MAX_LENGTH];
	int		error;

	error = 0;
	root = root->branches->content;
	path = root->content;
	if (!getcwd(cwd, PWD_PATH_MAX_LENGTH))
	{
		printf(DEAD_DIRECTORY_ERROR);
		error = 1;
	}
	else if (chdir(path[0]) < 0)
	{
		printf("minishell: %s: %s\n", path[0], strerror(errno));
		error = 2;
	}
	return (error);
}

int	verif_redirect(t_tree *root)
{
	int		error;
	t_tree	*tmp;

	error = 0;
	tmp = root->branches->content;
	if (tmp->type == REDIRECT)
	{
		create_file_redirect(tmp);
		if (chdir(ft_lstgetenv("HOME")) < 0)
			printf("minishell: %s: %s\n", (char *)root->content,
				strerror(errno));
	}
	else if (root->branches->next)
	{
		tmp = root->branches->next->content;
		create_file_redirect(tmp);
		error = change_dir(root);
	}
	else
		error = change_dir(root);
	return (error);
}

int	quit_cd(char *home)
{
	if (!home)
	{
		printf("minishell: cd: HOME not set\n");
		return (1);
	}
	return (0);
}

int	b_cd(void *sh, t_tree *root)
{
	t_shell	*shell;
	char	*env_home;
	int		error;

	error = 0;
	shell = sh;
	if (root->branches)
		error = verif_redirect(root);
	else
	{
		env_home = ft_lstgetenv("HOME");
		if (!env_home || !ft_strlen(env_home))
			return (quit_cd(env_home));
		if (chdir(env_home) < 0)
			printf("minishell: %s: %s\n", (char *)root->content,
				strerror(errno));
		free(env_home);
	}
	if (error)
		return (error - 1);
	if (!getcwd(shell->pwd_path, PWD_PATH_MAX_LENGTH))
		ft_bzero(shell->pwd_path, PWD_PATH_MAX_LENGTH);
	free(shell->pwd);
	shell->pwd = NULL;
	set_current_dir(shell);
	return (0);
}
