#include "minishell.h"

int	controller(char c, t_shell *sh, int *i)
{
	if (c == '\n')
		return (1);
	else if (c == EOF && !(*i))
	{
		ft_bzero(sh->cmd, CMD_MAX_LENGTH);
		ft_strlcpy(sh->cmd, sh->b_str[B_EXIT], sh->b_strlen[B_EXIT] + 1);
		return (1);
	}
	if (c > 0)
		sh->cmd[(*i)++] = (char)c;
	return (0);
}

/*
** TO-DO HERE:
**		- command historic with arrow keys up/down
*/
void	read_line(t_shell *sh)
{
	int	c;
	int	i;

	ft_bzero(sh->cmd, CMD_MAX_LENGTH);
	i = 0;
	while (1)
	{
		c = ft_getchar();
		if (controller(c, sh, &i))
			break ;
	}
}

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
	char	tmp[CMD_MAX_LENGTH];
	int		i;
	int		j;
	int		error;

	read_line(sh);
	if (!sh->cmd[0] || ft_str_isspace(sh->cmd))
		return (EXIT_SUCCESS);
	push_to_history(sh);
	if (!ft_memcmp(sh->cmd, "exit", 5)) { // TO REMOVE !
		printf("\nexit\n");
		free_shell(sh);
		exit(0);
	}
	ft_bzero(tmp, CMD_MAX_LENGTH);
	error = 0;
	i = 0;
	j = 0;
	while (sh->cmd[i])
	{
		error = process_line(tmp, sh, &i, &j);
		if (error)
			return (error);
	}
	error = tokenize(tmp, sh);
	return (error);
}
