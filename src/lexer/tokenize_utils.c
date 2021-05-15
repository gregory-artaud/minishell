#include "minishell.h"

void	skip_spaces(char s[CMD_MAX_LENGTH], int *i)
{
	while (s[*i] && ft_isspace(s[*i]))
		(*i)++;
}

t_token	*create_token(int type, char *value)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = ft_strdup(value);
	if (!new->value)
		return (NULL);
	return (new);
}

int	is_redirect(char s[CMD_MAX_LENGTH], int *i)
{
	int	res;

	res = 0;
	res += !ft_memcmp(s + *i, REDIRECT_OUTPUT_TOKEN, R_O_T_LEN);
	res += !ft_memcmp(s + *i, REDIRECT_INPUT_TOKEN, R_I_T_LEN);
	res += !ft_memcmp(s + *i, REDIRECT_OUTPUT_APPEND_TOKEN, R_O_A_T_LEN);
	return (res);
}

int	is_separator(char s[CMD_MAX_LENGTH], int *i)
{
	return (!ft_memcmp(s + *i, SEPARATOR_SEPARATOR_TOKEN, S_S_T_LEN)
		|| !ft_memcmp(s + *i, SEPARATOR_PIPE_TOKEN, S_P_T_LEN));
}
