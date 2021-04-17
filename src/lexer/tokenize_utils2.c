#include "minishell.h"

void	free_token(void *t)
{
	t_token	*token;

	token = (t_token *)t;
	if (!token)
		return ;
	if (token->value)
		free(token->value);
	free(token);
}
