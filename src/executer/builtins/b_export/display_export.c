#include "minishell.h"

char	**list_to_char(t_list *env)
{
	char	**tableau;
	int		i;

	tableau = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	i = 0;
	while (env)
	{
		tableau[i] = malloc(sizeof(char) * (ft_strlen(env->content) + 1));
		tableau[i] = ft_strncpy(tableau[i], env->content, ft_strlen(env->content));
		i++;
		env = env->next;
	}
	tableau[i] = NULL;
	return (tableau);
}

void	print_export(char *str, int fd)
{
	write(fd, "declare -x ", 11);
	while (*str != '=')
	{
		write(fd, str, 1);
		str++;
	}
	write(fd, str, 1);
	str++;
	write(fd, "\"", 1);
	write(fd, str, ft_strlen(str));
	write(fd, "\"\n", 2);
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

void	display_export(t_list *env, int fd)
{
	char	**tableau;
	int		i;

	tableau = sort_env(env);
	i = 0;
	while (tableau[i])
	{
		print_export(tableau[i], fd);
		free(tableau[i]);
		i++;
	}
	free(tableau);
}
