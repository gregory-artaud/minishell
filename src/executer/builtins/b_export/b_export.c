#include "minishell.h"

int	ft_verif_var_env(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && i != 0)
			return (1);
		i++;
	}
	return (0);
}

int	brw_env(t_list *env, char *var)
{
	while (env)
	{
		if (ft_strlen_sep(env->content, '=') == ft_strlen_sep(var, '='))
		{
			if (!ft_strncmp(env->content, var, ft_strlen_sep(var, '=')))
			{
				env->content = ft_strncpy(env->content, var, ft_strlen(var));
				return (EXIT_SUCCESS);
			}
		}
		env = env->next;
	}
	return (EXIT_FAILURE);
}

void	new_env(t_shell *sh, t_tree *root)
{
	char	**var;
	int		i;
	char	*content;

	root = root->branches->content;
	var = root->content;
	i = 0;
	while (i < root->size)
	{
		if (ft_verif_var_env(var[i]))
		{
			if (brw_env(sh->env, var[i]))
			{
				content = malloc(sizeof(char) * (ft_strlen(var[i]) + 1));
				content = ft_strncpy(content, var[i], ft_strlen(var[i]));
				ft_lstadd_back(&sh->env, ft_lstnew(content));
			}
		}
		i++;
	}
}

void	ft_export_red(t_tree *root, t_list *env, int display)
{
	char	**redirect;
	int		i;
	int		fd;

	redirect = root->content;
	i = 0;
	while (redirect[i])
	{
		i++;
		fd = open(redirect[i], O_RDWR | O_CREAT, S_IRWXU);
		i++;
	}
	if (display)
		display_export(env, fd);
}

int	b_export(void *sh, t_tree *root)
{
	t_shell	*shell;
	t_tree	*tmp;

	shell = sh;
	if (root->branches)
	{
			tmp = root->branches->content;
			if (tmp->type == REDIRECT)
				ft_export_red(tmp, shell->env, 1);
			else if (root->branches->next)
			{
				new_env(shell, root);
				ft_export_red(tmp, shell->env, 0);
			}
			else
				new_env(shell, root);
	}
	else
		display_export(shell->env, 1);
	return (0);
}
