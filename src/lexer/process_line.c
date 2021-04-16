#include "minishell.h"

int	process_env(char tmp[CMD_MAX_LENGTH], t_shell *sh, int *i, int *j)
{
	char	*name;
	char	*value;
	int		start;
	int		len;

	(*i)++;
	value = NULL;
	if (!ft_isalnum(sh->cmd[*i]) && sh->cmd[*i] != LAST_RETURN_CODE_VAR_NAME)
		return (no_env_var_name(tmp, j));
	else if (sh->cmd[*i] == LAST_RETURN_CODE_VAR_NAME && (*i)++)
		value = ft_itoa(sh->status);
	start = *i;
	while (ft_isalnum(sh->cmd[*i]))
		(*i)++;
	len = *i - start;
	name = ft_substr(sh->cmd, start, len);
	if (!value)
	{
		value = ft_strdup(getenv(name));
		free(name);
	}
	ft_strlcpy(tmp + *j, value, ft_strlen(value) + 1);
	*j += ft_strlen(value);
	if (value)
		free(value);
	return (EXIT_SUCCESS);
}


int	process_backslash(char tmp[CMD_MAX_LENGTH], t_shell *sh, int *i, int *j)
{
	(*i)++;
	if (!sh->cmd[*i])
		return (LEX_ERR_EOL_AFTER_ESCAPE);
	tmp[(*j)++] = sh->cmd[(*i)++];
	return (EXIT_SUCCESS);
}

int	process_double_quote(char tmp[CMD_MAX_LENGTH], t_shell *sh, int *i, int *j)
{
	int	error;

	(*i)++;
	while (sh->cmd[*i] && sh->cmd[*i] != DOUBLE_QUOTE)
		if (sh->cmd[*i] == BACKSLASH && is_special(sh->cmd[*i + 1]))
		{
			error = process_backslash(tmp, sh, i, j);
			if (error)
				return (error);
		}
		else if (sh->cmd[*i] == ENV_VARIABLE_TOKEN)
		{
			error = process_env(tmp, sh, i, j);
			if (error)
				return (error);
		}
		else
			tmp[(*j)++] = sh->cmd[(*i)++];
	if (sh->cmd[*i] != DOUBLE_QUOTE)
		return (LEX_ERR_OPEN_DOUBLE_QUOTE);
	(*i)++;
	return (EXIT_SUCCESS);
}

int	process_single_quote(char tmp[CMD_MAX_LENGTH], t_shell *sh, int *i, int *j)
{
	(*i)++;
	while (sh->cmd[*i] && sh->cmd[*i] != SINGLE_QUOTE)
		tmp[(*j)++] = sh->cmd[(*i)++];
	if (sh->cmd[*i] != SINGLE_QUOTE)
		return (LEX_ERR_OPEN_SINGLE_QUOTE);
	(*i)++;
	return (EXIT_SUCCESS);
}

int	process_line(char tmp[CMD_MAX_LENGTH], t_shell *sh, int *i, int *j)
{
	if (sh->cmd[*i] == BACKSLASH)
		return (process_backslash(tmp, sh, i, j));
	else if (sh->cmd[*i] == DOUBLE_QUOTE)
		return (process_double_quote(tmp, sh, i, j));
	else if (sh->cmd[*i] == SINGLE_QUOTE)
		return (process_single_quote(tmp, sh, i, j));
	else if (sh->cmd[*i] == ENV_VARIABLE_TOKEN)
		return (process_env(tmp, sh, i, j));
	else
		tmp[(*j)++] = sh->cmd[(*i)++];
	return (EXIT_SUCCESS);
}
