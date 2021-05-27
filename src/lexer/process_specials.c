#include "minishell.h"

char	*extract_name(char s[CMD_MAX_LENGTH], int *i)
{
	int		start;
	char	*name;

	if (s[*i] == LAST_RETURN_CODE_VAR_NAME && (*i)++)
		return (ft_strdup("?"));
	start = *i;
	while (ft_isalnum(s[*i]))
		(*i)++;
	name = ft_substr(s, start, *i - start);
	return (name);
}

char	*get_value(char *name)
{
	if (!ft_memcmp(name, "?", 2))
		return (ft_itoa(g_sh->status));
	return (ft_lstgetenv(name));
}

int	process_env(char s[CMD_MAX_LENGTH], int *i, char *wd, int *j)
{
	char	*name;
	char	*value;

	(*i)++;
	value = NULL;
	if (!ft_isalnum(s[*i]) && s[*i] != LAST_RETURN_CODE_VAR_NAME)
		return (no_env_var_name(wd, j));
	name = extract_name(s, i);
	if (!name)
		return (MALLOC_BREAK);
	value = get_value(name);
	free(name);
	if (!value)
		return (MALLOC_BREAK);
	ft_strlcpy(wd + *j, value, ft_strlen(value) + 1);
	*j += ft_strlen(value);
	free(value);
	return (EXIT_SUCCESS);
}

int	process_backslash(char s[CMD_MAX_LENGTH], int *i, char *wd, int *j)
{
	(void)wd;
	(void)j;
	(*i)++;
	if (!s[*i])
		return (LEX_ERR_EOL_AFTER_ESCAPE);
	wd[(*j)++] = s[(*i)++];
	return (EXIT_SUCCESS);
}

int	process_double_quote(char s[CMD_MAX_LENGTH], int *i, char *wd, int *j)
{
	int	error;

	(*i)++;
	while (s[*i] && s[*i] != DOUBLE_QUOTE)
	{
		if (s[*i] == BACKSLASH && is_special(s[*i + 1]))
		{
			error = process_backslash(s, i, wd, j);
			if (error)
				return (error);
		}
		else if (s[*i] == ENV_VARIABLE_PREFIX)
		{
			error = process_env(s, i, wd, j);
			if (error)
				return (error);
		}
		else
			wd[(*j)++] = s[(*i)++];
	}
	if (s[*i] != DOUBLE_QUOTE)
		return (LEX_ERR_OPEN_DOUBLE_QUOTE);
	(*i)++;
	return (EXIT_SUCCESS);
}

int	process_single_quote(char s[CMD_MAX_LENGTH], int *i, char *wd, int *j)
{
	(*i)++;
	while (s[*i] && s[*i] != SINGLE_QUOTE)
		wd[(*j)++] = s[(*i)++];
	if (s[*i] != SINGLE_QUOTE)
		return (LEX_ERR_OPEN_SINGLE_QUOTE);
	(*i)++;
	return (EXIT_SUCCESS);
}
