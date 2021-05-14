#include "minishell.h"

int	process_env(char s[CMD_MAX_LENGTH], int *i, char *wd, int *j)
{
	char	*name;
	char	*value;
	int		start;
	int		len;

	(*i)++;
	value = NULL;
	if (!ft_isalnum(s[*i]) && s[*i] != LAST_RETURN_CODE_VAR_NAME)
		return (no_env_var_name(wd, j));
	else if (s[*i] == LAST_RETURN_CODE_VAR_NAME && (*i)++)
		value = ft_itoa(g_sh->status);
	start = *i;
	while (ft_isalnum(s[*i]))
		(*i)++;
	len = *i - start;
	name = ft_substr(s, start, len);
	if (!value)
	{
		value = ft_strdup(getenv(name));
		free(name);
	}
	ft_strlcpy(wd + *j, value, ft_strlen(value) + 1);
	*j += ft_strlen(value);
	if (value)
		free(value);
	return (EXIT_SUCCESS);
}

int	process_backslash(char s[CMD_MAX_LENGTH], int *i, char *wd, int *j)
{
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
