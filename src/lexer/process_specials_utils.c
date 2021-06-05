#include "minishell.h"

char	*extract_value(char *env)
{
	char	**s;
	char	*res;

	s = ft_split(env, '=');
	if (!s)
		return (NULL);
	if (ft_arrlen(s) != 2)
	{
		ft_free_strarray(s);
		return (ft_strdup(""));
	}
	res = s[1];
	free(s[0]);
	free(s);
	return (res);
}

char	*ft_lstgetenv(char *name)
{
	t_list	*current;
	char	*cname;
	int		len;

	len = ft_strlen(name);
	current = g_sh->env;
	while (current)
	{
		cname = (char *)current->content;
		if (!ft_memcmp(cname, name, len) && cname[len] == '=')
			return (extract_value(cname));
		current = current->next;
	}
	return (NULL);
}

int	no_env_var_name(char tmp[CMD_MAX_LENGTH], int *j)
{
	tmp[(*j)++] = ENV_VARIABLE_PREFIX;
	return (EXIT_SUCCESS);
}

int	is_special(char c)
{
	return (c == BACKSLASH || c == DOUBLE_QUOTE
		|| c == ENV_VARIABLE_PREFIX || c == SINGLE_QUOTE);
}
