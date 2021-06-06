#include "minishell.h"

char	**free_and_exit(char **t)
{
	int	i;

	i = -1;
	while (t[++i])
		free(t[i]);
	free(t);
	return (NULL);
}

char	**list_to_char(t_list *env)
{
	char	**tableau;
	int		i;

	tableau = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	if (!tableau)
		return (NULL);
	i = 0;
	while (env)
	{
		tableau[i] = malloc(sizeof(char) * (ft_strlen(env->content) + 1));
		if (!tableau[i])
			return (free_and_exit(tableau));
		tableau[i] = ft_strncpy(tableau[i], env->content,
				ft_strlen(env->content));
		i++;
		env = env->next;
	}
	tableau[i] = NULL;
	return (tableau);
}

void	print_export(char *str)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	while (*str != '=' && *str)
	{
		ft_putchar_fd(*str, STDOUT_FILENO);
		str++;
	}
	if (*str == '=')
	{
		ft_putchar_fd(*str, STDOUT_FILENO);
		str++;
		ft_putchar_fd(DOUBLE_QUOTE, STDOUT_FILENO);
		ft_putstr_fd(str, STDOUT_FILENO);
		ft_putendl_fd("\"", STDOUT_FILENO);
	}
	else
		ft_putchar_fd('\n', STDOUT_FILENO);
}

char	**sort_env(t_list *env)
{
	char	**tableau;
	char	**begin;
	int		i;
	int		y;
	char	*tmp;

	tableau = list_to_char(env);
	begin = tableau;
	y = 0;
	while (begin[y])
	{
		i = 0;
		while (tableau[i])
		{
			if (ft_strncmp(begin[y], tableau[i], ft_strlen(begin[y])) < 0)
			{
				tmp = begin[y];
				begin[y] = tableau[i];
				tableau[i] = tmp;
			}
			i++;
		}
		y++;
	}
	return (tableau);
}

void	display_export(t_list *env)
{
	char	**tableau;
	int		i;

	tableau = sort_env(env);
	i = 0;
	while (tableau[i])
	{
		print_export(tableau[i]);
		free(tableau[i]);
		i++;
	}
	free(tableau);
}
