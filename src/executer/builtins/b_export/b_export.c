#include "minishell.h"

int	ft_verif_var_env(char *str)
{
	int	i;

	i = 0;
	if ((str[i] > 47 && str[i] < 58) || str[i] == '=')
		return (0);
	while (str[i] != '=' && str[i])
	{
		if (str[i] > 122 || str[i] == 96 || (str[i] > 90 && str[i] < 95) \
		|| (str[i] > 57 && str[i] < 65) || (str[i] > 32 && str[i] < 43) \
		|| (str[i] > 43 && str[i] < 48) || (str[i] == 43 && str[i + 1] != '='))
			return (0);
		i++;
	}
	if (str[i] == '=' && str[i - 1] == '+')
		return (2);
	return (1);
}

int	brw_env(t_list *env, char *var, int plus)
{
	while (env)
	{
		if (ft_strlen_sep(env->content, '=') == ft_strlen_sep(var, '=') \
		|| (ft_strlen_sep(env->content, '=') == ft_strlen_sep(var, '+')))
		{
			if (!ft_strncmp(env->content, var, ft_strlen_sep(var, '=')) \
			|| !ft_strncmp(env->content, var, ft_strlen_sep(var, '+')))
			{
				if (find_sep(env->content, '=') && plus == 2)
					env->content = free_env_join_sep(env->content);
				if (plus == 2)
					env->content = free_env_join(env->content, var);
				else if (!find_sep(var, '='))
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
	int		plus;

	root = root->branches->content;
	var = root->content;
	i = 0;
	while (i < root->size)
	{
		plus = ft_verif_var_env(var[i]);
		if (plus)
		{
			if (brw_env(sh->env, var[i], plus))
			{
				if (plus == 2)
					var[i] = free_not_env(var[i]);
				content = malloc(sizeof(char) * (ft_strlen(var[i]) + 1));
				content = ft_strncpy(content, var[i], ft_strlen(var[i]));
				ft_lstadd_back(&sh->env, ft_lstnew(content));
			}
		}
		else
			printf("minishell: export: '%s': not a valid identifier\n", var[i]);
		i++;
	}
}

void	ft_export_red(t_tree *root, t_list *env, int display)
{
	int	fd;

	fd = create_file_redirect(root);
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
