#include "minishell.h"

void	print_token(t_list *lst)
{
	t_list	*current;
	t_token	*token;

	if (!lst)
		return ;
	current = lst;
	while (current)
	{
		token = (t_token *)current->content;
		printf("token: %p\n", token);
		printf("\ttype: ");
		if (token->type == EXECUTABLE)
			printf("EXECUTABLE\n");
		else if (token->type == ARGUMENT)
			printf("ARGUMENT\n");
		else if (token->type == REDIRECT)
			printf("REDIRECT\n");
		else if (token->type == FILE_PATH)
			printf("FILE_PATH\n");
		else if (token->type == SEPARATOR)
			printf("SEPARATOR\n");
		printf("\tvalue: %s\n", token->value);
		printf("|\nv\n");
		current = current->next;
	}
}

int	lexer(t_shell *sh)
{
	int		error;

	read_line(sh);
	sh->cmd = (char *)sh->cmd_history->content;
	if (!sh->cmd[0] || ft_str_isspace(sh->cmd))
		return (EXIT_SUCCESS);
	error = push_to_history(sh);
	if (error)
		return (error);
	error = tokenize(sh);
	return (error);
}
